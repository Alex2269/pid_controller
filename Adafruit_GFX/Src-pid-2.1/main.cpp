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

#include "pid.h"

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

struct pid_controller_t pid_pump;

int main(void)
{
  gfx_open(tft.width(),tft.height(),"tft emulation");
  sinus_fill();

  // INIT PID_CONTROLLER
  static volatile float output = 0.0f;
  pid_init_controller(&pid_pump);
  pid_set_current_time(&pid_pump, current_timestamp_ns());
  pid_set_sample_time(&pid_pump, 10); // update every 10 nsec
  pid_set_tunings(&pid_pump, 0.250f, 0.150f, 0.125f);
  pid_set_output_limits(&pid_pump, -1000.0f, 1000.0f);
  pid_set_setpoint(&pid_pump,450.0f); // задаем желаемое значение nernst
  // END INIT PID_CONTROLLER

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
      pid_set_setpoint(&pid_pump,sin_table_b[i&(sinus_points)]); // задаем желаемое значение nernst
      pid_compute(&pid_pump,  current_timestamp_ns(), output); // вычисление коэфициентов
      output = pid_get_output(&pid_pump);
      tft.fillRect(i/*pos_x*/ , output/2+tft.height()/2, 2,2, WHITE); // id

      if( !(i % 32) ) draw_dynamic_grid(i-33);
      sleep_cycle(2500);
      // --
      gfx_flush(); // update the graphics
      // usleep(50);
    }
  }

  gfx_flush(); // update the graphics
  usleep(4e5);
}

