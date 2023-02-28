#include "utils.hpp"

#include "raylib.h"

namespace utils {

void DrawText(const char* text, Vector2 pos, Color color, float font_size,
              float spacing) {
    constexpr int default_font_size = 64;
    static Font font =
        LoadFontEx("data/open_sans.ttf", default_font_size, nullptr, 0);

    Vector2 pos_vec{static_cast<float>(pos.x), static_cast<float>(pos.y)};
    DrawTextEx(font, text, pos_vec, font_size, spacing, color);
}

Vector2 MeasureText(const char* text, float font_size, float spacing) {
    constexpr int default_font_size = 64;
    static Font font =
        LoadFontEx("data/open_sans.ttf", default_font_size, nullptr, 0);

    return MeasureTextEx(font, text, font_size, spacing);
}

}  // namespace utils
