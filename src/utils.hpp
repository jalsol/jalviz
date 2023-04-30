#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <cstring>
#include <random>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raylib.h"

/**
 * @brief The utility functions
 */

namespace utils {

/**
 * @brief Draws text with custom font size and spacing
 *
 * @param text The drawn text
 * @param pos The position of the text
 * @param color The color of the text
 * @param font_size The font size of the text
 * @param spacing The spacing of the text
 */
void DrawText(const char* text, Vector2 pos, Color color, float font_size,
              float spacing);

/**
 * @brief Measures the text with custom font size and spacing
 *
 * @param text The measured text
 * @param font_size The font size of the text
 * @param spacing The spacing of the text
 * @return Vector2 The size of the text
 */
Vector2 MeasureText(const char* text, float font_size, float spacing);

/**
 * @brief Get a random number in the range [low, high]
 *
 * @tparam T Integral type
 * @param low The lower bound
 * @param high The upper bound
 * @return T The random number
 */
template<typename T>
T get_random(T low, T high) {
    if (low > high) {
        return low;
    }

    static std::random_device ran_dev;
    static std::mt19937 prng(ran_dev());
    std::uniform_int_distribution<T> dist{low, high};
    return dist(prng);
}

/**
 * @brief Extracts integers from a string separated by commas
 *
 * @param str The string
 * @return core::Deque<int> The extracted data
 */
core::Deque<int> str_extract_data(
    char str[constants::text_buffer_size]);  // NOLINT

/**
 * @brief Checks if a value is in range [min_val, max_val]
 *
 * @param num The value
 * @retval true The value is in range
 * @retval false The value is not in range
 */
bool val_in_range(int num);

/**
 * @brief Tells the compiler that this branch is unreachable
 */
void unreachable();

/**
 * @brief Splits a string into tokens
 *
 * @param str The string
 * @param delim The delimiter
 * @param save_ptr The save pointer
 * @return char* The token
 */
char* strtok(char* str, const char* delim, char** save_ptr);

/**
 * @brief Converts a hex string to a color
 * @param str The string
 */
Color color_from_hex(const std::string& hex);

/**
 * @brief Returns the color of the text based on the background color
 * @param color The background color
 * @retval BLACK The text color is black
 * @retval WHITE The text color is white
 */
Color adaptive_text_color(Color bg_color);

}  // namespace utils

#endif  // UTILS_HPP_
