#ifndef QUILL_ASCII_GRAPHIC_H_
#define QUILL_ASCII_GRAPHIC_H_

#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern float HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;

// ((2 * x) / x_width) - 1
float normalize_x(unsigned int x_width, float x) {
  return ((2 * x) / x_width) - 1;
}

// ((2 * y) / y_height) - 1
float normalize_y(unsigned int y_height, float y) {
  return ((2 * y) / y_height) - 1;
}

// `Q_clear` clears a `WBuffer` using the provided fill character
int Q_clear(WBuffer *buffer, const char fill) {
  if (buffer == NULL)
    return 0;
  
  for (unsigned int i = 0; i < buffer->height * buffer->width; ++i)
    buffer->pixels[i] = fill;
  return 1;
}

// `Q_plotVertex` takes normalized coordinates [-1, 1] as input.
int Q_plotVertex(WBuffer *buffer, const char fill, float x, float y) {
  if (buffer == NULL)
    return 0;

  x = ((x + 1) * (buffer->width) * 0.5);
  y = ((y + 1) * (buffer->height) * 0.5);
  
  unsigned int pos = (unsigned int)(y * buffer->width + x);
  buffer->pixels[pos] = fill;

  return 1;
}

// `Q_drawVector` draws a vector from points (x1, y1) to (x2, y2) using the provided fill character
int Q_drawVector(
  WBuffer *buffer,
  const char fill,
  float x1,
  float y1, 
  float x2,
  float y2
) {
  if (buffer == NULL)
    return 0;
  
  x1 = ((x1 + 1) * (buffer->width) * 0.5);
  y1 = ((y1 + 1) * (buffer->height) * 0.5);
  x2 = ((x2 + 1) * (buffer->width) * 0.5);
  y2 = ((y2 + 1) * (buffer->height) * 0.5);

  if ((x1 < 0 || x1 > buffer->width) || (x2 < 0 || x2 >buffer->width) || (y1 < 0 || y1 > buffer->height) || (y2 < 0 || y2 > buffer->height)) {
    printf("Error: Vertex (%.2f, %.2f) out of bounds!\n\t~ Process terminated\n", x1 > x2 ? x1 : x2, y1 > y2 ? y1 : y2);
    return 0;
  }

  float dx = x2 - x1;
  float dy = y2 - y1;
  int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

  float xIncrement = dx / steps;
  float yIncrement = dy / steps;
  float x = x1, y = y1;

  for (int k = 0; k <= steps; ++k) {
    unsigned int index = (unsigned int)round(x) + (unsigned int)round(y) * buffer->width;

    if (index < buffer->width * buffer->height) {
      buffer->pixels[index] = fill;
    }

    x += xIncrement;
    y += yIncrement;
  }

  return 1;
}

#endif // QUILL_ASCII_GRAPHIC_H_
