#include "graphicstest.h"

extern Adafruit_GFX tft;

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

  // if(i > 125 && i < 255)
  //   sin_table_b[i] = 150.0;
}

void sinus_fill(void)
{
  for (uint32_t i=0; i<sinus_points; i++)
  {
    sin_init(i);
  }
}

void sinusoide_draw(void)
{
  static int16_t shift = tft.height()/2;
  for(uint16_t i = 32; i < tft.width()-32 ; i++)
  {
    static volatile uint16_t x;
    x = i & sinus_points;
    if(x>=sinus_points) x-=sinus_points;
    tft.writeFillRect(i, (sin_table_a[x]/2) + shift ,2,2, BLUE);
    tft.writeFillRect(i, (sin_table_b[x]/2) + shift ,2,2, GREEN);
    tft.writeFillRect(i, (sin_table_c[x]/2) + shift ,2,2, RED);
  }
  usleep(150);
}

void draw_dot_grid(void)
{
  #define space 8
  #define x_pos 31
  #define y_pos 16
  #define cell  32
  #define limit_below 15
  // osMutexWait(Display_MutexHandle, portMAX_DELAY); // mutex on
  for(uint16_t y = y_pos; y<tft.height()-limit_below; y+=space)
  for(uint16_t x = x_pos ; x<tft.width()-cell; x+=cell) tft.fillRect(x, y, 2,2, WHITE);
  for(uint16_t y = y_pos; y<tft.height()-limit_below; y+=cell)
  for(uint16_t x = x_pos ; x<tft.width()-cell; x+=space) tft.fillRect(x, y, 2,2, LIME);
  // osMutexRelease(Display_MutexHandle); // mutex off
}

void draw_dynamic_grid(int16_t shiftx)
{
  if(shiftx < 12) return;
  #define y_pos 16
  #define cell 33
  #define limit_below 15
  // osMutexAcquire(Display_MutexHandle, portMAX_DELAY);
  // osMutexWait(Display_MutexHandle, portMAX_DELAY); // mutex on
  for(uint16_t y = y_pos; y < tft.height()-limit_below ;y+= 8)
  for(uint16_t x = shiftx; x < cell + shiftx; x+=32) tft.fillRect(x, y, 2,2, CYAN);
  for(uint16_t y = y_pos; y < tft.height()-limit_below ;y+=32)
  for(uint16_t x = shiftx; x < cell + shiftx; x+=8 ) tft.fillRect(x, y, 2,2, WHITE);
  // osMutexRelease(Display_MutexHandle); // mutex off
}

unsigned long testText(void) {
  tft.fillScreen(BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(RED); tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  //start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles(void) {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
       cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  n     = MIN(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      LCD_Color565_to_Color16(0, 0, i>>1));
      //BLUE);
  }

  return micros() - start;
}

unsigned long testFilledTriangles(void) {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for(i=MIN(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
    LCD_Color565_to_Color16(0, i>>1, i>>1));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
    LCD_Color565_to_Color16(i>>1, i>>1, 0));
  }

  return t;
}

unsigned long testRoundRects(void) {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  w     = MIN(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, LCD_Color565_to_Color16(i>>1, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects(void) {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(BLACK);
  start = micros();
  for(i=MIN(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, LCD_Color565_to_Color16(0, i>>1, 0));
  }

  return micros() - start;
}

