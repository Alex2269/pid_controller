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

#include "FastPID.h"

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


float Kp=0.05, Ki=0.250, Kd=0.05, Hz=1.25;
int output_bits = 16;
bool output_signed = true;
int setpoint = 0;
int feedback = 0;
int output = 0;

int main(void)
{
  gfx_open(tft.width(),tft.height(),"tft emulation");
  sinus_fill();

  tft.fillScreen(BLACK);
  sinusoide_draw();

  tft.setFont(&Ubuntu12pt7b);
  tft.setCursor(32, 100);
  tft.setTextColor(YELLOW);
  tft.setTextSize(1);
  tft.println("Example pid regulation");

  FastPID_setCoefficients(Kp, Ki, Kd, Hz);
  FastPID_setOutputConfig(output_bits, output_signed);

  while(1)
  {
    for(int16_t i=16;i<tft.width()-16;i++)
    {
      setpoint = sin_table_b[i&(sinus_points)]/2;
      feedback = output = FastPID_step(setpoint, feedback);
      tft.fillRect(i/*pos_x*/ , output+tft.height()/2, 2,2, CYAN); // id

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

