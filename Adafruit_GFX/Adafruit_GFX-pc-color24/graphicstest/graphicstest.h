#ifndef __GRAPHICSTEST_HPP
#define __GRAPHICSTEST_HPP

#include <sys/param.h> // MIN MAX

#include "gfx.h"
#include "Adafruit_GFX.hpp"
#include "color.h"
#include "wiring_time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define sinus_points 255

// inline uint32_t LCD_Color888_to_Color24(uint8_t R8, uint8_t G8, uint8_t B8);
void sin_init(uint16_t i);
void sinus_fill(void);
void sinusoide_draw(void);
void draw_dot_grid(void);
void draw_dynamic_grid(int16_t shiftx);
unsigned long testText(void);
unsigned long testLines(uint32_t color);
unsigned long testFilledCircles(uint8_t radius, uint32_t color);
unsigned long testCircles(uint8_t radius, uint32_t color);
unsigned long testTriangles(void);
unsigned long testFilledTriangles(void);
unsigned long testRoundRects(void);
unsigned long testFilledRoundRects(void);

#ifdef __cplusplus
}
#endif

#endif // __GRAPHICSTEST_HPP
