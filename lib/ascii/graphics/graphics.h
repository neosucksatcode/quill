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

// `Q_clear()` clears a `WBuffer` using the provided fill character
int Q_clear(WBuffer *buffer, const char fill) {
  if (buffer == NULL)
    return 0;
  
  for (unsigned int i = 0; i < buffer->height * buffer->width; ++i)
    buffer->pixels[i] = fill;
  return 1;
}

// `Q_plotVertex()` takes normalized coordinates [-1, 1] as input.
int Q_plotVertex(WBuffer *buffer, const char fill, float x, float y) {
  if (buffer == NULL)
    return 0;

  x = ((x + 1) * (buffer->width) * 0.5);
  y = ((y + 1) * (buffer->height) * 0.5);
  
  unsigned int pos = (unsigned int)(y * buffer->width + x);
  buffer->pixels[pos] = fill;

  return 1;
}

#define CS_INSIDE 0 // 0000
#define CS_LEFT   1 // 0001
#define CS_RIGHT  2 // 0010
#define CS_BOTTOM 4 // 0100
#define CS_TOP    8 // 1000

static int compute_out_code(float x, float y, int width, int height) {
    int code = CS_INSIDE;
    if (x < 0.0f)        code |= CS_LEFT;
    else if (x > width)  code |= CS_RIGHT;
    if (y < 0.0f)        code |= CS_BOTTOM;
    else if (y > height) code |= CS_TOP;
    return code;
}

// `Q_drawVector()` draws a vector from points (x1, y1) to (x2, y2) using the provided fill character
int Q_drawVector(
    WBuffer *buffer,
    const char fill,
    float x1, float y1,
    float x2, float y2
) {
    if (!buffer) return 0;

    // Transform NDC → pixel coords
    x1 = (x1 + 1.0f) * buffer->width  * 0.5f;
    y1 = (y1 + 1.0f) * buffer->height * 0.5f;
    x2 = (x2 + 1.0f) * buffer->width  * 0.5f;
    y2 = (y2 + 1.0f) * buffer->height * 0.5f;

    int out1 = compute_out_code(x1, y1, buffer->width, buffer->height);
    int out2 = compute_out_code(x2, y2, buffer->width, buffer->height);

    // Cohen–Sutherland clipping loop
    while (1) {
        if ((out1 | out2) == 0) {
            // both inside → accept
            break;
        } else if (out1 & out2) {
            // both share an outside zone → trivial reject
            return 0;
        } else {
            // some segment is outside, clip it
            float x, y;
            int outcodeOut = out1 ? out1 : out2;

            if (outcodeOut & CS_TOP) {
                x = x1 + (x2 - x1) * (buffer->height - y1) / (y2 - y1);
                y = buffer->height;
            } else if (outcodeOut & CS_BOTTOM) {
                x = x1 + (x2 - x1) * (0.0f - y1) / (y2 - y1);
                y = 0.0f;
            } else if (outcodeOut & CS_RIGHT) {
                y = y1 + (y2 - y1) * (buffer->width - x1) / (x2 - x1);
                x = buffer->width;
            } else { // CS_LEFT
                y = y1 + (y2 - y1) * (0.0f - x1) / (x2 - x1);
                x = 0.0f;
            }

            // replace outside endpoint with intersection
            if (outcodeOut == out1) {
                x1 = x; y1 = y;
                out1 = compute_out_code(x1, y1, buffer->width, buffer->height);
            } else {
                x2 = x; y2 = y;
                out2 = compute_out_code(x2, y2, buffer->width, buffer->height);
            }
        }
    }

    // now (x1,y1)-(x2,y2) is fully inside; do your DDA
    float dx = x2 - x1, dy = y2 - y1;
    int steps = (fabsf(dx) > fabsf(dy)) ? (int)fabsf(dx) : (int)fabsf(dy);
    if (steps == 0) {
        // single point
        unsigned idx = (unsigned)roundf(x1) + (unsigned)roundf(y1) * buffer->width;
        if (idx < buffer->width * buffer->height)
            buffer->pixels[idx] = fill;
        return 1;
    }

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1, y = y1;
    for (int i = 0; i <= steps; ++i) {
        unsigned idx = (unsigned)roundf(x) + (unsigned)roundf(y) * buffer->width;
        if (idx < buffer->width * buffer->height)
            buffer->pixels[idx] = fill;
        x += xInc;
        y += yInc;
    }

    return 1;
}

#endif // QUILL_ASCII_GRAPHIC_H_
