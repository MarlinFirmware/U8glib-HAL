/**
 * u8g_line.c
 *
 * Universal 8bit Graphics Library
 *
 * Copyright (c) 2012, olikraus@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or other
 *   materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "u8g.h"

void u8g_DrawLine(u8g_t *u8g, u8g_uint_t x1, u8g_uint_t y1, u8g_uint_t x2, u8g_uint_t y2) {
  // no BBX intersection check at the moment, should be added...

  u8g_uint_t dx = (x1 > x2) ? x1 - x2 : x2 - x1;
  u8g_uint_t dy = (y1 > y2) ? y1 - y2 : y2 - y1;

  u8g_uint_t tmp;
  uint8_t swapxy = 0;
  if (dy > dx) {
    swapxy = 1;
    tmp = dx; dx =dy; dy = tmp;
    tmp = x1; x1 =y1; y1 = tmp;
    tmp = x2; x2 =y2; y2 = tmp;
  }
  if (x1 > x2) {
    tmp = x1; x1 =x2; x2 = tmp;
    tmp = y1; y1 =y2; y2 = tmp;
  }
  u8g_int_t err = dx >> 1;
  u8g_int_t ystep = (y2 > y1 ) ? 1 : -1;
  u8g_uint_t y = y1;

#ifndef  U8G_16BIT
  if (x2 == 255)
    x2--;
#else
  if (x2 == 0xffff)
    x2--;
#endif

  for (u8g_uint_t x = x1; x <= x2; x++) {
    if (swapxy == 0)
      u8g_DrawPixel(u8g, x, y);
    else
      u8g_DrawPixel(u8g, y, x);
    err -= (uint8_t)dy;
    if (err < 0) {
      y += (u8g_uint_t)ystep;
      err += (u8g_uint_t)dx;
    }
  }
}
