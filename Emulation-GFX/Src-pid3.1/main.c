#include "vga_adafruit.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
// include <inttypes.h>
#include "color.h"
#include "fonts_all_includes.h"

#include "pid_controller.h"

#define WIDTH 800
#define HEIGHT 480
#define delay(a) usleep(a*1000)

/**
*
* ┌───────────────────┬───────────────┬─────────┐
* │ Interface         │ Attribute     │  Value  │
* ├───────────────────┼───────────────┼─────────┤
* │ usleep()          │ Thread safety │ MT-Safe │
* └───────────────────┴───────────────┴─────────┘
*
**/

int64_t current_timestamp_ms()
{
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  int64_t milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
  // printf("milliseconds: %lld\n", milliseconds);
  return milliseconds;
}

int64_t current_timestamp_ns()
{
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  int64_t nanoseconds = (int64_t)(te.tv_sec) * (int64_t)1000000000 + (int64_t)(te.tv_usec);
  // printf("nanoseconds: %lld\n", nanoseconds);
  return nanoseconds;
}

void sleep_cycle(int64_t cycle_count)
{
  int64_t count=0;
  for(count=0;count<cycle_count;count++)
  {
    __asm volatile ("nop");
  }
}

#define sinus_points 255
float PI = 3.14159;
float sin_table_a[sinus_points];
float sin_table_b[sinus_points];
float sin_table_c[sinus_points];

void sin_init(uint16_t i)
{
  sin_table_c[(i+(sinus_points/3*1)) & (sinus_points)]=
  sin_table_b[(i+(sinus_points/3*2)) & (sinus_points)]=
  sin_table_a[(i+(sinus_points/3*3)) & (sinus_points)]=
  ((sin((float) i*(2*PI/sinus_points)))*(sinus_points/2));

  if(i > 125 && i < 255)
    sin_table_b[i] = 150.0;
}

static void sinus_fill(void)
{
  for (uint32_t i=0; i<sinus_points; i++)
  {
    sin_init(i);
  }
}

void sinusoide_draw(void)
{
  static int16_t shift = 320;
  for(uint16_t i = 32; i < Display_Get_WIDTH()-32 ; i++)
  {
    static volatile uint16_t x;
    x = i & sinus_points;
    if(x>=sinus_points) x-=sinus_points;
    // fillRect(i, (sin_table_a[x]/2) + shift ,1,1, BLUE);
    fillRect(i, (sin_table_b[x]/2) + shift ,1,1, GREEN);
    // fillRect(i, (sin_table_c[x]/2) + shift ,1,1, RED);
  }
  usleep(150);
}

void draw_dot_grid(void)
{
  // osMutexWait(Display_MutexHandle, portMAX_DELAY); // mutex on
  for(uint16_t y = 16;y<Display_Get_HEIGHT()-15;y+= 8)
  for(uint16_t x = 16; x<Display_Get_WIDTH()-15; x+=32) fillRect(x, y, 1,1, LIGHTBLUE);
  for(uint16_t y = 16;y<Display_Get_HEIGHT()-15;y+=32)
  for(uint16_t x = 16; x<Display_Get_WIDTH()-15; x+=8 ) fillRect(x, y, 1,1, LIGHTBLUE);
  // osMutexRelease(Display_MutexHandle); // mutex off
}

void draw_dynamic_grid(int16_t shiftx)
{
  if(shiftx < 12) return;
  #define y_pos 16
  #define ceil_x 33
  #define limit_below 15
  // osMutexAcquire(Display_MutexHandle, portMAX_DELAY);
  // osMutexWait(Display_MutexHandle, portMAX_DELAY); // mutex on
  for(uint16_t y = y_pos; y < Display_Get_HEIGHT()-limit_below ;y+= 8)
  for(uint16_t x = shiftx; x < ceil_x + shiftx; x+=32) fillRect(x, y, 1,1, CYAN);
  for(uint16_t y = y_pos; y < Display_Get_HEIGHT()-limit_below ;y+=32)
  for(uint16_t x = shiftx; x < ceil_x + shiftx; x+=8 ) fillRect(x, y, 1,1, CYAN);
  // osMutexRelease(Display_MutexHandle); // mutex off
}

int main(void)
{
  Display_Set_WIDTH(WIDTH);
  Display_Set_HEIGHT(HEIGHT);
  gfx_open(WIDTH,HEIGHT,"tft emulation");
  fillRect(0, 0, Display_Get_WIDTH(),Display_Get_HEIGHT(), BLACK);
  // draw_dot_grid();

  setTextSize(1);
  setCursor(32, 80);
  setTextColor(YELLOW);
  setTextBgColor(BLACK);
  // UG_FONT_set(&font_neuepixel_17X27);
  UG_FONT_set(&font_Ubuntu_13X24);
  // UG_FONT_set(&font_ClearSans_26X26);
  UG_PutString("Example pid regulations");
  // UG_PutString2("Example pid regulations", 4);

  for (uint32_t i=0; i<sinus_points; i++)
  {
    sin_init(i);
  }

  sinusoide_draw();

  //
  // PID Initialize
  // Description:
  //      Initializes a PIDControl instantiation. This should be called at least once
  //      before any other PID functions are called.
  // Parameters:
  //      pid - The address of a PIDControl instantiation.
  //      kp - Positive P gain constant value.
  //      ki - Positive I gain constant value.
  //      kd - Positive D gain constant value.
  //      sampleTimeSeconds - Interval in seconds on which PIDCompute will be called.
  //      minOutput - Constrain PID output to this minimum value.
  //      maxOutput - Constrain PID output to this maximum value.
  //      mode - Tells how the controller should respond if the user has taken over
  //             manual control or not.
  //             MANUAL:    PID controller is off. User can manually control the
  //                        output.
  //             AUTOMATIC: PID controller is on. PID controller controls the output.
  //      controllerDirection - The sense of direction of the controller
  //                            DIRECT:  A positive setpoint gives a positive output.
  //                            REVERSE: A positive setpoint gives a negative output.
  // Returns:
  //      Nothing.
  //
  // --

  static volatile float output = 0.0f;
  static PIDControl pid; // PIDControl struct instance
  // --
  // INIT PID_CONTROLLER
  // PIDInit(*pid, kp, ki, kd, sampleTime, minOutput, maxOutput, mode, Direction);
  PIDInit(&pid,0.250,0.125,0.125,0.75,-75000.0,75000.0,AUTOMATIC,DIRECT); // all one
  /*
  PIDTuningKpSet(&pid,0.250);
  PIDTuningKiSet(&pid,0.125);
  PIDTuningKdSet(&pid,0.125);
  PIDSampleTimeSet(&pid,0.75);
  PIDOutputLimitsSet(&pid,-75000.0,75000.0);
  PIDTuningsSet(&pid,0.250,0.125,0.125);
  PIDModeSet(&pid, AUTOMATIC);
  PIDControllerDirectionSet(&pid, DIRECT);
  */
  // END INIT PID_CONTROLLER
  // --

  while(1)
  {
    for(int16_t i=16;i<Display_Get_WIDTH()-16;i++)
    {
      // pid.iTerm = 0.0;
      PIDSetpointSet(&pid, sin_table_b[i&(sinus_points)]/2); // бажане задане значення
      PIDInputSet(&pid, output); // оновлене вхідне значення з АЦП або сенсору
      PIDCompute(&pid);
      output = PIDOutputGet(&pid); // отриманий результат PID_CONTROLLER
      PIDInputSet(&pid, 0);

      fillRect(i, output+320, 1,1, WHITE); // id

      if( !(i % 32) ) draw_dynamic_grid(i-33);
      sleep_cycle(25000);
      // --
      gfx_flush(); // update the graphics
      // usleep(50);
    }
  }
  gfx_flush(); // update the graphics
  usleep(4e6);
}

