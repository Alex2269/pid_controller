#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>

#include "gfx.h"
#include "Adafruit_GFX.hpp"
#include "color.h"
#include "wiring_time.h"

#include "graphicstest.h"
#include "fonts.h"

#include "pid_controller.h"

/**
*
* ┌───────────────────┬───────────────┬─────────┐
* │ Interface         │ Attribute     │  Value  │
* ├───────────────────┼───────────────┼─────────┤
* │ usleep()          │ Thread safety │ MT-Safe │
* └───────────────────┴───────────────┴─────────┘
*
**/

Adafruit_GFX tft = Adafruit_GFX(640, 480);

extern float sin_table_a[];
extern float sin_table_b[];
extern float sin_table_c[];

int main(void)
{

  gfx_open(tft.width(),tft.height(),"tft emulation");
  sinus_fill();

  tft.fillScreen(BLACK);
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

  tft.setFont(&Ubuntu12pt7b);
  tft.setCursor(32, 100);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  tft.println("Example pid regulation");

  while(1)
  {
    for(int16_t i=16;i<tft.width()-16;i++)
    {
      // pid.iTerm = 0.0;
      PIDSetpointSet(&pid, sin_table_b[i&(sinus_points)]/2); // бажане задане значення
      PIDInputSet(&pid, output); // оновлене вхідне значення з АЦП або сенсору
      PIDCompute(&pid);
      output = PIDOutputGet(&pid); // отриманий результат PID_CONTROLLER
      PIDInputSet(&pid, 0);

      tft.fillRect(i, output+tft.height()/2, 2,2, WHITE); // id

      if( !(i % 32) ) draw_dynamic_grid(i-33);
      sleep_cycle(25000);
      // --
      gfx_flush(); // update the graphics
      // usleep(50);
    }
  }

  gfx_flush(); // update the graphics
  usleep(4e5);
}

