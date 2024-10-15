#ifndef __pix_H
#define __pix_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include Library */
#include <X11/Xlib.h>
#include <stdint.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include "stdbool.h"
// #include "ftoa_impl.h"

void drawPixel(uint16_t x, uint16_t y, uint32_t color);
void gfx_color(int r, int g, int b);

#ifdef __cplusplus
}
#endif

#endif // __pix_H


