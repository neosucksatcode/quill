#ifndef QUILL_ASCII_WINDOW_H_
#define QUILL_ASCII_WINDOW_H_

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern float HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO;

// `WBuffer` is the struct for the front and back buffers
typedef struct {
  unsigned int width, height;
  char *pixels;
} WBuffer;

// `QWindow` is the main window struct
typedef struct {
  unsigned int front_idx, back_idx;
  WBuffer *buffers[2];
} QWindow;

// `Q_windowFront()` gets the pointer to the front buffer.
WBuffer* Q_windowFront(QWindow *window) {
  return window->buffers[window->front_idx];
}

// `Q_windowBack()` gets the pointer to the back buffer.
WBuffer* Q_windowBack(QWindow *window) {
  return window->buffers[window->back_idx];
}

// `Q_createWBuffer()` creates a `WBuffer` of provided width and height.
WBuffer* Q_createWBuffer(unsigned int width, unsigned int height) {
  WBuffer *buffer = (WBuffer*)malloc(sizeof(WBuffer));
  if (buffer == NULL)
    return NULL;

  width = (unsigned int)((float)width * HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO);

  buffer->pixels = (char*)malloc(sizeof(char) * height * width);
  if (buffer->pixels == NULL) {
    free(buffer);
    return NULL;
  }

  buffer->width = width;
  buffer->height = height;

  return buffer;
}

// `Q_createWindow()` creates a `QWindow` of provided width and height.
QWindow* Q_createWindow(unsigned int width, unsigned int height) {
  QWindow *window = (QWindow*)malloc(sizeof(QWindow));
  if (window == NULL)
    return NULL;

  window->buffers[0] = Q_createWBuffer(width, height);
  if (window->buffers[0] == NULL) {
    free(window);
    return NULL;
  }

  window->buffers[1] = Q_createWBuffer(width, height);
  if (window->buffers[1] == NULL) {
    free(window->buffers[0]);
    free(window);
    return NULL;
  }

  window->front_idx = 0;
  window->back_idx = 1;
  
  return window;
}

void __printQWindowToTerminal(WBuffer *buffer) {
  for (unsigned int h = 0; h < buffer->height; ++h) {
    for (unsigned int w = 0; w < buffer->width; ++w) {
      write(STDOUT_FILENO, &buffer->pixels[h * buffer->width + w], 1);
    }
    write(STDOUT_FILENO, "\n", 1);
  }
}

// `Q_swapBuffers()` swaps the front and back buffer pointers and displays front buffer.
int Q_swapBuffers(QWindow *window) {
  if (window == NULL)
    return 0;

  unsigned int idx = window->front_idx;
  window->front_idx = window->back_idx;
  window->back_idx = idx;
  
  // Print the front buffer to the terminal
  __printQWindowToTerminal(window->buffers[window->front_idx]);

  return 1;
}

// `Q_freeWindow()` deallocates a `QWindow` created by `Q_createWindow`.
int Q_freeWindow(QWindow *window) {
  if (window == NULL)
    return 0;

  free(window->buffers[0]->pixels);
  free(window->buffers[1]->pixels);
  free(window->buffers[0]);
  free(window->buffers[1]);
  free(window);
  return 1;
}

// `Q_clearTerminal()` clears the terminal
void Q_clearTerminal(void) { puts("\033[2J\033[H"); }

#endif // QUILL_ASCII_WINDOW_H_
