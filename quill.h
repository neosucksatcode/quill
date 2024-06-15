// Move all to quill.c

#ifndef QUILL_H_
#define QUILL_H_

#ifdef QUILL_ASCII_

#pragma once
#include "./lib/return.h"
#include "./lib/ascii/define/define.h"
#include "./lib/ascii/window/window.h"
#include "./lib/ascii/graphic/graphic.h"
#include "./lib/ascii/geometry/geometry.h"

#else

#include "./lib/std/define/define.h"
#include "./lib/std/window/window.h"
#include "./lib/std/graphics/graphics.h"
#include "./lib/std/geometry/geometry.h"

#endif // QUILL_ASCII_
#endif // QUILL_H_
