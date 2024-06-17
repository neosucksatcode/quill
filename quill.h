// Move all to quill.c

#ifndef QUILL_H_
#define QUILL_H_

#ifdef QUILL_ASCII_

#pragma once
#include "./lib/define.h"
#include "./lib/ascii/window/window.h"
#include "./lib/ascii/graphic/graphic.h"
#include "./lib/ascii/geometry/geometry.h"

int init_Quill(const float ratio) {
  HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO = ratio;
  return 0;
}

#else

#include "./lib/define.h"
#include "./lib/std/window/window.h"
#include "./lib/std/graphics/graphics.h"
#include "./lib/std/geometry/geometry.h"

int init_Quill() { return 0; }

#endif // QUILL_ASCII_
#endif // QUILL_H_
