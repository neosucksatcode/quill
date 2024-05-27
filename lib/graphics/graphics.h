#ifndef QUILL_GRAPHICS_H_
#define QUILL_GRAPHICS_H_

#pragma once
#include "../config.h"
#include "../definitions.h"
#include <math.h>
#include <stdio.h>

int plot_Vertex(Quill_Window *window, u8 color, const char fill, float x,
                float y) {
  int QUILL_ERROR = QUILL_SUCCESS;
  if (window == NULL)
    DEFER(WINDOW_IS_NULL);

  x *= HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;

  u32 position = (u32)(y * window->width + x);
  window->pixels[position] = fill;
  window->colors[position] = color;

defer:
  return QUILL_ERROR;
}

int draw_Vector(Quill_Window *window, u8 color, const char fill, float x1,
                float y1, float x2, float y2) {
  if (window == NULL) {
    fprintf(stderr, "Error: Quill_Window* is NULL\n");
    return WINDOW_IS_NULL;
  }

  // printf("x1: %f, y1: %f, x2: %f, y2: %f\n", x1, y1, x2, y2);

  x1 *= HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;
  x2 *= HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;

  if ((x1 > window->width || x1 < 0) || (x2 > window->width || x2 < 0) ||
      (y1 > window->height || y1 < 0) || (y2 > window->height || y2 < 0)) {
    printf(
        "Error: Vertex (%.2f, %.2f) out of bounds!\n\t~ Process terminated\n",
        x1 > x2 ? x1 : x2, y1 > y2 ? y1 : y2);
    return VERTEX_OUT_OF_BOUNDS;
  }

  float dx = x2 - x1;
  float dy = y2 - y1;
  int steps;
  float xIncrement, yIncrement, x = x1, y = y1;

  if (fabs(dx) > fabs(dy)) {
    steps = fabs(dx);
  } else {
    steps = fabs(dy);
  }

  xIncrement = dx / steps;
  yIncrement = dy / steps;

  for (int k = 0; k <= steps; k++) {
    u32 index = (u32)round(x) + (u32)round(y) * window->width;

    if (/* index >= 0 && */ index < window->width * window->height) {
      window->pixels[index] = fill;
      window->colors[index] = color;
    }

    x += xIncrement;
    y += yIncrement;
  }

  return QUILL_SUCCESS;
}

#endif // QUILL_GRAPHICS_H_