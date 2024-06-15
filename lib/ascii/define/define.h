#ifndef QUILL_ASCII_DEFINE_H_
#define QUILL_ASCII_DEFINE_H_

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
  u32 height, width;
  char *pixels;
  u8 *colors;
} QuillWindow;

#endif // QUILL_ASCII_DEFINE_H_