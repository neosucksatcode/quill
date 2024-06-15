#ifndef QUILL_ASCII_GRAPHIC_H_
#define QUILL_ASCII_GRAPHIC_H_

#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../config.h"
#include "../../return.h"
#include "../define/define.h"
#include "../geometry/geometry.h"

int plot_Vertex(QuillWindow *window, u8 color, const char fill, float x,
                float y)
{
  if (window == NULL)
    return WINDOW_IS_NULL;

  x *= HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;

  u32 position = (u32)(y * window->width + x);
  window->pixels[position] = fill;
  window->colors[position] = color;
  return QUILL_SUCCESS;
}

int draw_Vector(QuillWindow *window, u8 color, const char fill, float x1,
                float y1, float x2, float y2)
{
  if (window == NULL) {
    fprintf(stderr, "Error: QuillWindow* is NULL\n");
    return WINDOW_IS_NULL;
  }

  x1 *= HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;
  x2 *= HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;

  if ((x1 < 0 || x1 > window->width) || (x2 < 0 || x2 > window->width) || (y1 < 0 || y1 > window->height) || (y2 < 0 || y2 > window->height)) {
    printf("Error: Vertex (%.2f, %.2f) out of bounds!\n\t~ Process terminated\n", x1 > x2 ? x1 : x2, y1 > y2 ? y1 : y2);
    return VERTEX_OUT_OF_BOUNDS;
  }

  float dx = x2 - x1;
  float dy = y2 - y1;
  int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

  float xIncrement = dx / steps;
  float yIncrement = dy / steps;
  float x = x1, y = y1;

  for (int k = 0; k <= steps; ++k) {
    u32 index = (u32)round(x) + (u32)round(y) * window->width;

    if (index < window->width * window->height) {
        window->pixels[index] = fill;
        window->colors[index] = color;
    }

    x += xIncrement;
    y += yIncrement;
  }

  return QUILL_SUCCESS;
}

int draw_Triangle(QuillWindow *window, u8 color, const char fill, float v1x,
                  float v1y, float v2x, float v2y, float v3x, float v3y)
{
  int state = QUILL_SUCCESS;
  state = draw_Vector(window, color, fill, v1x, v1y, v2x, v2y);
  state = draw_Vector(window, color, fill, v2x, v2y, v3x, v3y);
  state = draw_Vector(window, color, fill, v3x, v3y, v1x, v1y);
  return state;
}

int write_Text(QuillWindow *window, u8 color, char *text, float x1,
               float y1, float x2, float y2)
{
  if (window == NULL) {
    fprintf(stderr, "Error: QuillWindow* is NULL\n");
    return WINDOW_IS_NULL;
  }

  float h_x1 = x1 * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;
  float h_x2 = x2 * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;

  if ((h_x1 > window->width || h_x1 < 0) || (h_x2 > window->width || h_x2 < 0) || (y1 > window->height || y1 < 0) || (y2 > window->height || y2 < 0)) {
    printf("Error: Vertex (%.2f, %.2f) out of bounds!\n\t~ Process terminated\n", h_x1 > h_x2 ? h_x1 : h_x2, y1 > y2 ? y1 : y2);
    return VERTEX_OUT_OF_BOUNDS;
  }

  float dx = h_x2 - h_x1;
  float dy = y2 - y1;
  int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

  float xIncrement = dx / steps;
  float yIncrement = dy / steps;
  float x = h_x1, y = y1;

  size_t i = 0, length = strlen(text);

  for (int k = 0; k <= steps; ++k) {
    u32 index = (u32)round(x) + (u32)round(y) * window->width;

    if (index < window->width * window->height) {
      if (!isspace(text[i])) {
        window->pixels[index] = text[i];
        window->colors[index] = color;
      } else if (text[i] == '\n') {
        y += 1.0f;  // Move cursor down one row
      } else if (text[i] == '\t') {
        x += 4 * xIncrement;  // Move cursor right by 4 spaces
      }

      x += xIncrement;
      y += yIncrement;
    }

    if (i >= length || i >= fabs(x2 - x1)) {
      break;
    } else {
      ++i;
    }
  }

  return QUILL_SUCCESS;
}

#endif // QUILL_ASCII_GRAPHIC_H_
