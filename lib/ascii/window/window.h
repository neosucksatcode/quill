#ifndef QUILL_ASCII_WINDOW_H_
#define QUILL_ASCII_WINDOW_H_

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../config.h"
#include "../../return.h"
#include "../../define.h"

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

typedef struct {
  u32 height, width;
  char *pixels;
  u8 *colors;
} QuillWindow;

void clear_Terminal(void) { puts("\033[2J\033[H"); }

int init_Window(QuillWindow *window, const u32 width, const u32 height)
{
  size_t size =
      (size_t)(height * width * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO);

  window->pixels = (char *)malloc(sizeof(char) * size);
  if (window->pixels == NULL)
    return FAILED_WINDOW_ALLOCATION;

  window->colors = (u8 *)malloc(sizeof(u8) * size);
  if (window->colors == NULL) {
    free(window->pixels);
    return FAILED_WINDOW_ALLOCATION;
  }

  window->height = height;
  window->width = (u8)(width * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO);
  return QUILL_SUCCESS;
}

QuillWindow *create_Window(const u32 width, const u32 height)
{
  QuillWindow *window = (QuillWindow*) malloc(sizeof(QuillWindow));
  if (window == NULL)
    return NULL;

  size_t size =
      (size_t)(height * width * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO);

  window->pixels = (char *)malloc(sizeof(char) * size);
  if (window->pixels == NULL) {
    free(window);
    return NULL;
  }

  window->colors = (u8 *)malloc(sizeof(u8) * size);
  if (window->colors == NULL) {
    free(window->pixels);
    free(window);
    return NULL;
  }

  window->height = height;
  window->width = (u8)(width * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO);
  return window;
}

int cleanUp_Window(QuillWindow *window)
{
  if (window == NULL)
    return WINDOW_IS_NULL;

  if (window->pixels != NULL) {
    free(window->pixels);
  }
  
  if (window->colors != NULL) {
    free(window->colors);
  }

  return QUILL_SUCCESS;
}

int free_Window(QuillWindow *window)
{
  if (window == NULL)
    return WINDOW_IS_NULL;

  if (window->pixels != NULL) {
    free(window->pixels);
  }
  
  if (window->colors != NULL) {
    free(window->colors);
  }

  free(window);
  return QUILL_SUCCESS;
}

int fill_Window(QuillWindow *window, const int color, const char fill)
{
  if (window == NULL)
    return WINDOW_IS_NULL;
  if (window->pixels == NULL)
    return WINDOW_PIXELS_IS_NULL;
  else if (window->colors == NULL)
    return WINDOW_COLORS_IS_NULL;

  for (u32 i = 0; i < window->height * window->width; ++i) {
    window->pixels[i] = fill;
    window->colors[i] = color;
  }

  return QUILL_SUCCESS;
}

int clear_Window(QuillWindow *window)
{
  if (window == NULL)
    return WINDOW_IS_NULL;
  if (window->pixels == NULL)
    return WINDOW_PIXELS_IS_NULL;
  else if (window->colors == NULL)
    return WINDOW_COLORS_IS_NULL;

  for (u32 i = 0; i < window->height * window->width; ++i) {
    window->pixels[i] = ' ';
    window->colors[i] = 0;
  }

  return QUILL_SUCCESS;
}

int output_Window(QuillWindow *window, const bool reset_color)
{
  if (window == NULL)
    return WINDOW_IS_NULL;
  if (window->pixels == NULL)
    return WINDOW_PIXELS_IS_NULL;

  for (u32 h = 0; h < window->height; ++h) {
    for (u32 w = 0; w < window->width; ++w) {
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

  return QUILL_SUCCESS;
}

int fast_output_Window(QuillWindow *window)
{
  if (window == NULL)
    return WINDOW_IS_NULL;
  if (window->pixels == NULL)
    return WINDOW_PIXELS_IS_NULL;

  for (u32 h = 0; h < window->height; ++h) {
    for (u32 w = 0; w < window->width; ++w) {
      write(STDOUT_FILENO, &window->pixels[h * window->width + w], 1);
    }
    write(STDOUT_FILENO, "\n", 1);
  }

  return QUILL_SUCCESS;
}

#endif // QUILL_ASCII_WINDOW_H_
