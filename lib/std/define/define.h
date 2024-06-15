#ifndef QUILL_STD_DEFINE_H_
#define QUILL_STD_DEFINE_H_

#pragma once
#include <stdint.h>

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
  u32 height, width;
  uint32_t *pixels;
} QuillWindow;

#endif // QUILL_STD_DEFINE_H_
