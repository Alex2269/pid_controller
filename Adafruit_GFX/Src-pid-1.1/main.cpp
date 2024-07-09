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

#include "PID.h"

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

  static volatile float measurement = 0.0f;
  static volatile float output = 0.0f;
  static volatile float result = 0.0f;
  PIDController_Init(&pid);

  gfx_open(tft.width(),tft.height(),"tft emulation");
  sinus_fill();

  tft.fillScreen(BLACK);
  sinusoide_draw();

  tft.setFont(&Ubuntu12pt7b);
  tft.setCursor(32, 100);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  tft.println("Example pid regulation");

  while(1)
  {
    for(int16_t i=16;i<tft.width()-16;i++)
    {
      /* Get measurement from system */
      output = PIDController_Get(&pid, measurement, result);
      /* Compute new control signal */
      // float PIDController_Update(&pid, setpoint, measurement);
      result = PIDController_Update(&pid, sin_table_b[i&(sinus_points)], output);

      tft.fillRect(i/*pos_x*/ , result+tft.height()/2/* + shift */ ,2,2, WHITE); // id

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

