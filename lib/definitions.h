#ifndef QUILL_DEFINTIONS_H_
#define QUILL_DEFINTIONS_H_

#define QUILL_SUCCESS 1

#define WINDOW_IS_NULL -1
#define WINDOW_PIXELS_IS_NULL -2
#define WINDOW_COLORS_IS_NULL -3

#define FAILED_WINDOW_ALLOCATION -4

#define VERTEX_OUT_OF_BOUNDS -5

#define DEFER(QUILL_ERROR_CODE)                                                \
  do {                                                                         \
    QUILL_ERROR = QUILL_ERROR_CODE;                                            \
    goto defer;                                                                \
  } while (0)

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
  u32 height, width;
  char *pixels;
  int *colors;
} Quill_Window;

// Remove later
#define QUILL_ASCII_

#endif // QUILL_DEFINTIONS_H_
