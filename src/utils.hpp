#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "raylib.h"

namespace utils {

void DrawText(const char* text, Vector2 pos, Color color, float font_size,
              float spacing);

Vector2 MeasureText(const char* text, float font_size, float spacing);

}  // namespace utils

#endif  // UTILS_HPP_
