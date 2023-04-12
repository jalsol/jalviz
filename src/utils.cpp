#include "utils.hpp"

#include <array>
#include <cmath>
#include <cstring>
#include <ios>
#include <sstream>

#include "constants.hpp"
#include "raylib.h"

namespace utils {

void DrawText(const char* text, Vector2 pos, Color color, float font_size,
              float spacing) {
    static Font font = LoadFontEx("data/open_sans.ttf",
                                  constants::default_font_size, nullptr, 0);

    Vector2 pos_vec{static_cast<float>(pos.x), static_cast<float>(pos.y)};
    DrawTextEx(font, text, pos_vec, font_size, spacing, color);
}

Vector2 MeasureText(const char* text, float font_size, float spacing) {
    static Font font = LoadFontEx("data/open_sans.ttf",
                                  constants::default_font_size, nullptr, 0);

    return MeasureTextEx(font, text, font_size, spacing);
}

core::Deque<int> str_extract_data(
    char str[constants::text_buffer_size]) {  // NOLINT
    char str_copy[constants::text_buffer_size];
    strncpy(str_copy, str, constants::text_buffer_size);

    char* save_ptr = nullptr;
    char* token = utils::strtok(str_copy, ",", &save_ptr);

    if (token == nullptr) {
        return {};
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

Color color_from_hex(const std::string& hex) {
    std::stringstream stream(hex + "ff");
    unsigned int value;
    stream >> std::hex >> value;
    return GetColor(value);
}

// https://stackoverflow.com/a/3943023
Color adaptive_text_color(Color bg_color) {
    constexpr std::array<float, 3> threshold{{0.2126, 0.7152, 0.0722}};
    const std::array<int, 3> colors = {{bg_color.r, bg_color.g, bg_color.b}};
    float sum = 0;

    for (auto i = 0; i < 3; ++i) {
        float value = (float)colors.at(i) / 255.0F;
        if (value <= 0.04045) {
            value /= 12.92;
        } else {
            value = std::pow(((value + 0.055) / 1.055), 2.4);
        }

        sum += value;
    }

    return (sum > 0.179) ? BLACK : WHITE;
}

}  // namespace utils
