#ifndef QUILL_STD_WINDOW_H_
#define QUILL_STD_WINDOW_H_

#pragma once
#include "../define/define.h"
typedef struct {
  u32 height, width;
  uint32_t *pixels;
} QuillWindow;

#endif // QUILL_STD_WINDOW_H_
