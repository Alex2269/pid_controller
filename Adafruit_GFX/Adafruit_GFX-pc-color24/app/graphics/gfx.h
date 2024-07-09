#ifndef __gfx_H
#define __gfx_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include Library */
#include <X11/Xlib.h>
// #include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <stdbool.h>

void gfx_open(int width, int height, const char *title);
void gfx_flush(void);

#ifdef __cplusplus
}
#endif

#endif // __gfx_H


