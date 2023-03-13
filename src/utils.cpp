#include "utils.hpp"

#include <cstring>

#include "gui/node_gui.hpp"
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

core::Deque<int> str_extract_data(
    char str[constants::text_buffer_size]) {  // NOLINT
    char* save_ptr = nullptr;
    char* token = utils::strtok(str, ",", &save_ptr);

    if (token == nullptr) {
        return {0};
    }

    core::Deque<int> ret;

    constexpr int base = 10;
    int num = static_cast<int>(std::strtol(token, nullptr, base));
    ret.push_back(num);

    while (true) {
        token = utils::strtok(nullptr, ",", &save_ptr);
        if (token == nullptr) {
            break;
        }

        num = static_cast<int>(std::strtol(token, nullptr, base));
        ret.push_back(num);
    }

    return ret;
}

bool val_in_range(int num) {
    return constants::min_val <= num && num <= constants::max_val;
}

void unreachable() {
#if defined(_MSC_VER)
    __assume(0);
#else
    __builtin_unreachable();
#endif
}

char* strtok(char* str, const char* delim, char** save_ptr) {
    return
#if defined(_MSC_VER)
        strtok_s(str, delim, save_ptr);
#else
        strtok_r(str, delim, save_ptr);
#endif
}

}  // namespace utils
