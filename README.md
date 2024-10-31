# Quill

Quill is a lightweight graphics library designed for 2D and 3D rendering. It provides a terminal-based solution for creating graphics directly within the terminal environment. The library is designed to be versatile and easy to use.

## General Information

Quill is designed to be a standalone graphics library which contains fascilities for regular graphcics programming as well as ANSI graphics in the terminal environment. Quill is built uppon a few core principles:

1. **Portability** ~ Compile `quill.h` to any platform, the library is written using souly standard C.

2. **Open source** ~ Quill is meant for everyone, feel free to rewrite the library to better fit your needs.

## Get Started

Start by cloning this repository into your project, let the new 'quill' folder be its own separate folder. Create a new folder named 'src' in the same scope as the 'quill' folder. Inside the 'src' folder create a C file 'main'. Now open the file. To utilize Quill in your project simply include its header and define what library you want to use. (Currently its only the ASCII library)

### *ASCII*

```c
#define QUILL_ASCII_
#include "../quill/quill.h"

int main(void) {
  Q_init(1.8f);
  QWindow *window = Q_createWindow(40, 40);
  Q_clear(window, ' ');
  Q_drawVector(Q_windowBack(window), '*', -1.0f, -1.0f, 1.0f, 1.0f);
  Q_swapBuffersWindow(window, true);
  Q_freeWindow(window);
  return 0;
}
```

By default a float `HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO` is set to equal `1.8f` and should be initialized with a different value using the `Q_init()` function before compiling to reflect what your terminal's ratio between character height and width is.

Now compile the translation unit (C file) to an executable using your favorite compiler. A good practice is to enable all warnings. E.g:

*Using GCC:*

`gcc -Wall -Wextra -o main main.c`

## The Library

### quill.h

```c
void Q_init(const float ratio) { ... }
```

`Q_init()` takes a `const float` as an argument and initializes the `HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO` to the provided value;

### window.h

*window.h* contains functions which modify and interact with `QWindow` and `WBuffer` and some which handle output to the terminal.

#### *'QWindow' && 'WBuffer'*

```c
typedef struct {
  unsigned int width, height;
  char *pixels;
} WBuffer;

// `QWindow` is the main window struct
typedef struct {
  unsigned int front_idx, back_idx;
  WBuffer *buffers[2];
} QWindow;
```

`WBuffer` is the struct for the front and back buffers.
`QWindow` is the main window struct type.

#### *'Q_clearTerminal()'*

```c
void Q_clearTerminal(void) { ... }
```

`Q_clearTerminal()` takes no arguments and returns nothing. It simply clears the terminal of any content.

#### *'Q_createWindow()'*

```c
QuillWindow *create_Window(const unsigned int width, const unsigned int height) { ... }
```

`Q_createWindow()` takes in two `unsigned int` width and height as arguments. It dynamically allocates memory for a QWindow and returns a `QWindow*` if successful, `NULL` if not.

#### *'Q_freeWindow()'*

```c
int Q_freeWindow(QWindow *window) { ... }
```

`Q_freeWindow()` takes a `QWindow*` window as an argument and deallocates its member variables as well as it self. Returns `1` if successful, `0` if not.

#### *'Q_swapBuffers()'*

```c
int Q_swapBuffers(QWindow *window) { ... }
```

`Q_swapBuffers()` takes a `QWindow*` as an argument and swaps the index of its front and back buffers.

### graphics.h

*graphics.h* contains functions which modify and interact with the values stored inside `QWindow` and `WBuffer`, e.g buffers and pixels.

#### *'Q_clear()'*

```c
int Q_clear(WBuffer* buffer, const char fill) { ... }
```

`Q_clear()` takes a `WBuffer*` buffer and a `const char` fill as arguments. If buffer is `NULL` it returns `0`. Returns `1` on success.

#### *'Q_plotVertex()'*

```c
int Q_plotVertex(WBuffer *buffer, const char fill, float x, float y) { ... }
```
`Q_plotVertex()` takes a `WBuffer*` buffer, a `const char` fill, and two `float` x and y as arguments. It plots a vertex in the buffer.  If the buffer is `NULL` it returns `0`. Returns `1` on success.

#### *'Q_drawVector()'*

```c
int Q_drawVector(WBuffer *buffer, const char fill, float x1, float y1, float x2, float y2) { ... }
```
`Q_drawVector()` takes a `WBuffer*` buffer, a `const char` fill, and four `float` x1, y1, x2 and y2 as arguments. It draws a vector in the buffer.  If the buffer is `NULL` it returns `0`. Returns `1` on success.

```c
float normalize_x(unsigned int x_width, float x) { ... }
```

`Q_drawVector()` takes an `unsigned int` x_width and a `float` x as arguments. Normalizes x in the range -1.0 to 1.0 according to the x_width value.

```c
float normalize_y(unsigned int y_height, float y) { ... }
```

`Q_drawVector()` takes an `unsigned int` y_height and a `float` y as arguments. Normalizes y in the range -1.0 to 1.0 according to the y_height value.
