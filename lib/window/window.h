#ifndef QUILL_WINDOW_H_
#define QUILL_WINDOW_H_

#include "../definitions.h"

#ifdef QUILL_ASCII_

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../config.h"

#define ANSI_COLOR_WHITE "\033[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"

#define ANSI_WHITE 0
#define ANSI_RED 1
#define ANSI_GREEN 2
#define ANSI_BLUE 3
#define ANSI_YELLOW 4
#define ANSI_MAGENTA 5

int init_Window(Quill_Window *window, const u32 width, const u32 height) {
  int QUILL_ERROR = QUILL_SUCCESS;
  size_t size =
      (size_t)(height * width * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO);

  window->pixels = (char *)malloc(sizeof(char) * size);
  if (window->pixels == NULL)
    DEFER(FAILED_WINDOW_ALLOCATION);

  window->colors = (int *)malloc(sizeof(int) * size);
  if (window->colors == NULL) {
    free(window->pixels);
    DEFER(FAILED_WINDOW_ALLOCATION);
  }

  window->height = height;
  window->width = (int)(width * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO);

defer:
  return QUILL_ERROR;
}

int free_Window(Quill_Window *window) {
  int QUILL_ERROR = 0;
  if (window == NULL)
    DEFER(WINDOW_IS_NULL);
  if (window->pixels == NULL)
    DEFER(WINDOW_PIXELS_IS_NULL);

  free(window->pixels);
defer:
  return QUILL_ERROR;
}

int fill_Window(Quill_Window *window, const int color, const char fill) {
  int QUILL_ERROR = QUILL_SUCCESS;
  if (window == NULL)
    DEFER(WINDOW_IS_NULL);
  if (window->pixels == NULL)
    DEFER(WINDOW_PIXELS_IS_NULL);
  else if (window->colors == NULL)
    DEFER(WINDOW_COLORS_IS_NULL);

  for (u32 i = 0; i < window->height * window->width; i++) {
    window->pixels[i] = fill;
    window->colors[i] = color;
  }

defer:
  return QUILL_ERROR;
}

int clear_Window(Quill_Window *window) {
  int QUILL_ERROR = QUILL_SUCCESS;
  if (window == NULL)
    DEFER(WINDOW_IS_NULL);
  if (window->pixels == NULL)
    DEFER(WINDOW_PIXELS_IS_NULL);
  else if (window->colors == NULL)
    DEFER(WINDOW_COLORS_IS_NULL);

  for (u32 i = 0; i < window->height * window->width; i++) {
    window->pixels[i] = ' ';
    window->colors[i] = 0;
  }

defer:
  return QUILL_ERROR;
}

int output_Window(Quill_Window *window, const bool reset_color) {
  int QUILL_ERROR = QUILL_SUCCESS;
  if (window == NULL)
    DEFER(WINDOW_IS_NULL);
  if (window->pixels == NULL)
    DEFER(WINDOW_PIXELS_IS_NULL);

  for (u32 h = 0; h < window->height; h++) {
    for (u32 w = 0; w < window->width; w++) {
      const char *color_code;
      switch (window->colors[h * window->width + w]) {
      case ANSI_RED:
        color_code = ANSI_COLOR_RED;
        break;
      case ANSI_GREEN:
        color_code = ANSI_COLOR_GREEN;
        break;
      case ANSI_BLUE:
        color_code = ANSI_COLOR_BLUE;
        break;
      case ANSI_YELLOW:
        color_code = ANSI_COLOR_YELLOW;
        break;
      case ANSI_MAGENTA:
        color_code = ANSI_COLOR_MAGENTA;
        break;
      case ANSI_WHITE:
      default:
        color_code = ANSI_COLOR_WHITE;
        break;
      }
      write(STDOUT_FILENO, color_code, strlen(color_code));
      write(STDOUT_FILENO, &window->pixels[h * window->width + w], 1);
    }
    write(STDOUT_FILENO, "\n", 1);
  }

  if (reset_color) {
    write(STDOUT_FILENO, ANSI_COLOR_WHITE, strlen(ANSI_COLOR_WHITE));
  }

defer:
  return QUILL_ERROR;
}

int fast_output_Window(Quill_Window *window) {
  int QUILL_ERROR = QUILL_SUCCESS;
  if (window == NULL)
    DEFER(WINDOW_IS_NULL);
  if (window->pixels == NULL)
    DEFER(WINDOW_PIXELS_IS_NULL);

  for (u32 h = 0; h < window->height; h++) {
    for (u32 w = 0; w < window->width; w++) {
      write(STDOUT_FILENO, &window->pixels[h * window->width + w], 1);
    }
    write(STDOUT_FILENO, "\n", 1);
  }

defer:
  return QUILL_ERROR;
}

#else

/*

typedef struct {
  u32 height, width;
  uint32_t *pixels;
} Quill_Window;

*/

#endif // QUILL_ASCII_

#endif // QUILL_WINDOW_H_