// Move all to quill.c

#ifndef QUILL_H_
#define QUILL_H_

#ifdef QUILL_ASCII_

#pragma once
#include "./lib/ascii/window/window.h"
#include "./lib/ascii/graphics/graphics.h"

float HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO = 1.8f;

int Q_init(const float ratio) {
  HEIGHT_TO_WIDTH_PIXEL_DIMENSION_RATIO = ratio;
  return 0;
}

#else

#include "./lib/define.h"
#include "./lib/std/window/window.h"
#include "./lib/std/graphics/graphics.h"

int Q_init() { return 0; }

#endif // QUILL_ASCII_
#endif // QUILL_H_
