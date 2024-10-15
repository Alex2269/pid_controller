#include "vga_adafruit.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include "color.h"
#include "fonts_all_includes.h"

#include "PID.h"

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
  /* Controller parameters */
  #define PID_KP 0.45f
  #define PID_KI 0.050f
  #define PID_KD 0.075f
  #define PID_TAU 0.1f
  #define PID_LIM_MIN -1000.0f
  #define PID_LIM_MAX 1000.0f
  #define PID_LIM_MIN_INT -15.0f
  #define PID_LIM_MAX_INT 15.0f
  #define SAMPLE_TIME 0.225f

  /* Initialise PID controller */
  PIDController pid =
  {
    PID_KP, PID_KI, PID_KD,
    PID_TAU,
    PID_LIM_MIN, PID_LIM_MAX,
    PID_LIM_MIN_INT, PID_LIM_MAX_INT,
    SAMPLE_TIME
  };

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

  static volatile float measurement = 0.0f;
  static volatile float output = 0.0f;
  static volatile float result = 0.0f;
  PIDController_Init(&pid);

  while(1)
  {
    for(int16_t i=16;i<Display_Get_WIDTH()-16;i++)
    {
      /* Get measurement from system */
      output = PIDController_Get(&pid, measurement, result);
      /* Compute new control signal */
      // float PIDController_Update(&pid, setpoint, measurement);
      result = PIDController_Update(&pid, sin_table_b[i&(sinus_points)], output);

      fillRect(i/*pos_x*/ , result+320/* + shift */ ,1,1, WHITE); // id

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

