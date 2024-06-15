# Quill

Quill is a lightweight graphics library designed for 2D and 3D rendering. It provides a terminal-based solution for creating graphics directly within the terminal environment. The library is designed to be versatile and easy to use.

# General Information

Quill is designed to be a standalone graphics library which contains fascilities for regular graphcics programming as well as ANSI graphics in the terminal environment. Quill is built uppon a few core principles:

1. Portability
   Compile `quill.h` to any platform, the library is written using souly standard C.

2. Opensource
   Quill is meant for everyone, feel free to rewrite the library to better fit your needs.

3. Optional Speed
   Quill's ASCII library supports different means of rendering, most notably `fast_output_window()` which prints the characters without any colors. The function is designed to output each frame as quickly as possible.

4. Minimal Debugging
   The majority of all the functions in Quill return debugging codes to allow for easier error handling. Some functions such as `create_Window()` do not return a debugging code, in this case it returns a `QuillWindow` pointer. `clear_Terminal()` takes no parameters and returns nothing (`void`).
