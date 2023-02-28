#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <random>

#include "raylib.h"

namespace utils {

void DrawText(const char* text, Vector2 pos, Color color, float font_size,
              float spacing);

Vector2 MeasureText(const char* text, float font_size, float spacing);

template<typename T>
T get_random(T low, T high) {
    static std::random_device ran_dev;
    static std::mt19937 prng(ran_dev());
    static std::uniform_int_distribution<T> dist{low, high};
    return dist(prng);
}

}  // namespace utils

#endif  // UTILS_HPP_
