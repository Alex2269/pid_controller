#include "pixel.h"

extern Display *gfx_display;
extern Window gfx_window;
extern GC gfx_gc;
extern int gfx_fast_color_mode;

uint16_t LCD_Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

inline uint32_t LCD_Color565_to_888(uint16_t color) {
  return (((color & 0xF800) << 8) | ((color & 0x7E0) << 5) | ((color & 0x1F) << 3));  // transform to rrrrrrxx ggggggxx bbbbbbxx
}

inline uint8_t LCD_Color565_to_R(uint16_t color) {
  return ((color & 0xF800) >> 8);  // transform to rrrrrrxx
}

inline uint8_t LCD_Color565_to_G(uint16_t color) {
  return ((color & 0x7E0) >> 3);  // transform to ggggggxx
}

inline uint8_t LCD_Color565_to_B(uint16_t color) {
  return ((color & 0x1F) << 3);  // transform to bbbbbbxx
}

void drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
  uint8_t r,g,b;
  b = LCD_Color565_to_B(color);
  g = LCD_Color565_to_G(color);
  r = LCD_Color565_to_R(color);
  gfx_color(r, g, b);
  XDrawPoint(gfx_display,gfx_window,gfx_gc,x,y);
}

/* Change the current drawing color. */
void gfx_color( int r, int g, int b )
{
  XColor color;
  if(gfx_fast_color_mode) 
  {
    /* If this is a truecolor display, we can just pick the color directly. */
    color.pixel = ((b&0xff) | ((g&0xff)<<8) | ((r&0xff)<<16) );
  }
  XSetForeground(gfx_display, gfx_gc, color.pixel);
}
