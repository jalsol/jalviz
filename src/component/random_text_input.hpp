#ifndef COMPONENT_RANDOM_TEXT_INPUT_HPP_
#define COMPONENT_RANDOM_TEXT_INPUT_HPP_

#include <string>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raylib.h"
#include "text_input.hpp"

namespace component {

/**
 * @brief Text input that supports random values
 */

class RandomTextInput : public TextInput {
public:
    using TextInput::size;

    /**
     * @brief Constructs a RandomTextInput object
     */
    RandomTextInput() = default;

    /**
     * @brief Constructs a RandomTextInput object
     * @param label the label of the random text input
     */
    RandomTextInput(const char* label);

    using TextInput::extract_values;

    /**
     * @brief Renders the random text input, updates the head position with
     * offset
     * @param options_head the head position of the options
     * @param head_offset the offset of the head position
     */
    void render_head(float& options_head, float head_offset);

    /**
     * @brief Checks if the random text input is interacted with
     * @return true if the random text input is interacted with, false otherwise
     */
    bool interact();

    /**
     * @brief Sets the min value of the random text input
     * @param value the min value of the random text input
     */
    void set_random_min(int value);

    /**
     * @brief Sets the max value of the random text input
     * @param value the max value of the random text input
     */
    void set_random_max(int value);

private:
    /**
     * @brief The min value of the random text input
     */
    int m_random_min{constants::min_val};

    /**
     * @brief The max value of the random text input
     */
    int m_random_max{constants::max_val};

    /**
     * @brief Whether the random text input is interacted with
     */
    bool m_set_random{};
};

}  // namespace component

#endif  // COMPONENT_RANDOM_TEXT_INPUT_HPP_
