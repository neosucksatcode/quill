# Quill

Quill is a lightweight graphics library designed for 2D and 3D rendering. It provides a terminal-based solution for creating graphics directly within the terminal environment. The library is designed to be versatile and easy to use.

## General Information

Quill is designed to be a standalone graphics library which contains fascilities for regular graphcics programming as well as ANSI graphics in the terminal environment. Quill is built uppon a few core principles:

1. **Portability** ~ Compile `quill.h` to any platform, the library is written using souly standard C.

2. **Open source** ~ Quill is meant for everyone, feel free to rewrite the library to better fit your needs.

3. **Optional Speed** ~ Quill's ASCII library supports different means of rendering, most notably `fast_output_window()` which prints the characters without any colors. The function is designed to output each frame as quickly as possible.

4. **Minimal Debugging** ~ The majority of all the functions in Quill return debugging codes to allow for easier error handling. Some functions such as `create_Window()` do not return a debugging code, in this case it returns a `QuillWindow*`. One function: `clear_Terminal()` takes no arguments and returns nothing (`void`).

## Get Started

Start by cloning this repository into your project, let the new 'quill' folder be its own separate folder. Create a new folder named 'src' in the same scope as the 'quill' folder. Inside the 'src' folder create a C file 'main'. Now open the file. To utilize Quill in your project simply include its header and define what library you want to use.

### *ASCII*

```c
#define QUILL_ASCII_
#include "../quill/quill.h"

int main(void) {
  QuillWindow *window = createWindow(30, 30);
  clear_Window(window);
  fill_Window(window, ANSI_BLUE, '.');
  output_Window(window, true);
  free_Window(window);
  return 0;
}
```

By default a constant named `HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO` is set to equal `1.8f` and should be changed before compiling to reflect what your terminal's ratio between character height and width is. This will later be replaced by a function for initializing Quill: `init_Quill()`.

### *STD*

```c
#include "../quill/quill.h"

int main(void) {
  QuillWindow *window = createWindow(30, 30);
  clear_Window(window);
  fill_Window(window, 0x000000);
  display_Window(window);
  free_Window(window);
  return 0;
}
```

Now compile the translation unit (C file) to an executable using your favorite compiler. A good practice is to enable all warnings. E.g:

_Using GCC:_

`gcc -Wall -Wextra -o main main.c`

## The Library

### define.h

*define.h* contains all of the general defintions which are used in multiple places in the codebase.

*'General Types and Debugging Codes'*

```c
#define QUILL_SUCCESS 1
#define WINDOW_IS_NULL -1
#define WINDOW_PIXELS_IS_NULL -2
#define WINDOW_COLORS_IS_NULL -3
#define FAILED_WINDOW_ALLOCATION -4
#define VERTEX_OUT_OF_BOUNDS -5

typedef unsigned char u8;
typedef unsigned int u32;
// ...
```

Currently the only types defined in *define.h* are `u8` and `u32`.

### window.h

*window.h* contains function definitions for functions which modify Quill windows and some which handle output to the terminal or screen.

#### *'QuillWindow'*

```c
// ASCII

typedef struct {
  u32 height, width;
  char *pixels;
  u8 *colors;
} QuillWindow;
```

```c
// STD

typedef struct {
  u32 height, width;
  u32 *pixels;
} QuillWindow;
```

`QuillWindow` is a type defined struct which contains four member variables in the ASCII defintion and three in the STD defintion. The variables `height` and `width` are both of the `u32` type and specify the dimensions of the window. In the ASCII definition `pixels` is a `char*` which stores pixels as ASCII characters. In the STD definition `pixels` is a `u32*` which stores pixels in hexadecimal format e.g '0x000000'.

#### *'clear_Terminal()'*

```c
// ASCII

void clear_Terminal(void) { puts("\033[2J\033[H"); }
```

```c
// STD

void clear_Screen(void) { ... }
```

`clear_Terminal()` and `clear_Screen()` take no arguments and return nothing. They simply clear the terminal or screen of any content.

#### *'init_Window()'*

```c
int init_Window(QuillWindow *window, const u32 width, const u32 height) { ... }
```

`init_Window()` takes a `QuillWindow*` window, a `u32` width and a `u32` height as arguments. It initializes all member variables in a *__stack__* *__allocated__* `QuillWindow` and dynamically allocates memory on the heap for the pixels (and colors). Notice that the function call is identical between the ASCII definition and the STD definition however the implementations are marginally different. Returns `QUILL_SUCCESS` if successful, `FAILED_WINDOW_ALLOCATION` if not. 

#### *'create_Window()'*

```c
QuillWindow *create_Window(const u32 width, const u32 height) { ... }
```

`create_Window()` takes a `u32` width and a `u32` height as arguments. It dynamically allocates memory for a new QuillWindow. Returns a `QuillWindow*` if successful, `NULL` is not.

#### *'cleanUp_Window()'*

```c
int cleanUp_Window(QuillWindow *window) { ... }
```
`cleanUp_Window` takes a `QuillWindow*` window which points to a *__stack__* *__allocated__* `QuillWindow` as an argument and deallocates its member variables. Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL`.

#### *'free_Window()'*

```c
int free_Window(QuillWindow *window) { ... }
```

`free_Window()` takes a `QuillWindow*` window which points to a *__heap__* *__allocated__* `QuillWindow` as an argument and deallocates its member variables as well as it self. Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL`.

#### *'fill_Window()'*

```c
// ASCII

int fill_Window(QuillWindow *window, const u8 color, const char fill) { ... }
```

```c
// STD

int fill_Window(QuillWindow *window, const u32 color) { ... }
```

`fill_Window()` in the ASCII definition takes a `QuillWindow*` window, a `u8` color and a `char` fill as arguments. It fills the window's `pixels` with the character and appliet the color to all cells inside `colors`. Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL`, `WINDOW_PIXELS_IS_NULL` if `pixels` is `NULL` or `WINDOW_COLORS_IS_NULL` if `colors` is `NULL`. In the STD definition it takes a `QuillWindow*` and a `u32` color as arguments. Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL` or `WINDOW_PIXELS_IS_NULL` if `pixels` is `NULL`.

#### *'clear_Window()'*

```c
int clear_Window(QuillWindow *window) { ... }
```

`clear_Window()` takes a `QuillWindow*` window as an argument. In the ASCII definition it sets all of the pixels to a whitespace (' ') and the color to `ANSI_WHITE` (0). Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL`, `WINDOW_PIXELS_IS_NULL` if `pixels` is `NULL` or `WINDOW_COLORS_IS_NULL` if `colors` is `NULL`. In the STD definition it sets all pixels to be black ('0x000000'). Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL`.

#### *'output_Window'*

```c
// ASCII

int output_Window(QuillWindow *window, const bool reset_color) { ... }
```

`output_Window()` is only defined in the ASCII side of the quill library and it takes a `QuillWindow*` window and a `bool` reset_color as arguments. The function prints out all of the characters in `pixels` according to the coresponding color in `colors`. If reset_color is `true` it resets the color to `ANSI_WHITE`. Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL`, `WINDOW_PIXELS_IS_NULL` if `pixels` is `NULL` or `WINDOW_COLORS_IS_NULL` if `colors` is `NULL`.

#### *'fast_output_Window()'*

```c
int fast_output_Window(QuillWindow *window) { ... }
```

`fast_output_Window()` is also only defined in the ASCII side of the quill library and it takes a `QuillWindow*` window as an argument. The function prints out all of the characters in `pixels` and neglects the coresponding color in `colors`. Returns `QUILL_SUCCESS` if successful, `WINDOW_IS_NULL` if the `QuillWindow*` is `NULL` or `WINDOW_PIXELS_IS_NULL` if `pixels` is `NULL`.
