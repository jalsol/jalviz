#ifndef COMPONENT_TEXT_INPUT_HPP_
#define COMPONENT_TEXT_INPUT_HPP_

#include <string>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raylib.h"

namespace component {

/**
 * @brief Input for entering text
 */

class TextInput {
public:
    /**
     * @brief The size of the text input
     */
    static constexpr Vector2 size{200, 50};

    /**
     * @brief Constructs a TextInput object
     */
    TextInput() = default;

    /**
     * @brief Constructs a TextInput object
     * @param label the label of the text input
     */
    TextInput(const char* label);

    /**
     * @brief Renders the text input
     * @param x the x position of the text input
     * @param y the y position of the text input
     */
    void render(float x, float y);

    /**
     * @brief Renders the text input, updates the head position with offset
     * @param options_head the head position of the options
     * @param head_offset the offset of the head position
     */
    void render_head(float& options_head, float head_offset);

    /**
     * @brief Returns the input of the text input
     * @return the input of the text input
     */
    std::string get_input() const;

    /**
     * @brief Checks if the text input is active
     * @return true if the text input is active, false otherwise
     */
    bool is_active() const;

    /**
     * @brief Sets the input of the text input
     * @param input the input of the text input
     * @param len the length of the input
     */
    void set_input(const char* input, int len);

    /**
     * @brief Sets the label of the text input
     * @param label the label of the text input
     */
    void set_label(const char* const label);

    /**
     * @brief Extracts the values from the text input
     * @return the values from the text input
     */
    core::Deque<int> extract_values();

protected:
    /**
     * @brief The text input
     */
    char m_text_input[constants::text_buffer_size] = "";  // NOLINT

    /**
     * @brief Whether the text input is active
     */
    bool m_is_active{};

    /**
     * @brief The label of the text input
     */
    const char* m_label{};
};

}  // namespace component

#endif  // COMPONENT_TEXT_INPUT_HPP_
