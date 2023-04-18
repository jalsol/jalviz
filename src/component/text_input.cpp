#include "text_input.hpp"

#include <cstring>
#include <iostream>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raygui.h"
#include "settings.hpp"
#include "utils.hpp"

namespace component {

TextInput::TextInput(const char* label) : m_label{label} {}

void TextInput::render(float x, float y) {
    Rectangle shape{x, y, size.x, size.y};

    utils::DrawText(
        m_label, {x, y - 25},
        utils::adaptive_text_color(
            Settings::get_instance().get_color(Settings::num_color - 1)),
        20, 2);

    DrawRectangleRec(shape, RAYWHITE);

    if (GuiTextBox(shape, static_cast<char*>(m_text_input),
                   constants::text_buffer_size, m_is_active)) {
        m_is_active ^= 1;
    }
}

void TextInput::render_head(float& options_head, float head_offset) {
    render(options_head, constants::scene_height - size.y);
    options_head += (size.x + head_offset);
}

std::string TextInput::get_input() const { return {m_text_input}; }

bool TextInput::is_active() const { return m_is_active; }

void TextInput::set_label(const char* const label) { m_label = label; }

void TextInput::set_input(const char* input, int len) {
    std::strncpy(static_cast<char*>(m_text_input), input, len);
}

core::Deque<int> TextInput::extract_values() {
    core::Deque<int> nums = utils::str_extract_data(m_text_input);  // NOLINT
    return nums;
}

}  // namespace component
