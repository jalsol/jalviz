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

void TextInput::set_random_min(int value) { m_random_min = value; }

void TextInput::set_random_max(int value) { m_random_max = value; }

void TextInput::render(float& options_head, float head_offset) {
    Rectangle shape{options_head, constants::scene_height - size.y, size.x,
                    size.y};

    utils::DrawText(
        m_label, {options_head, constants::scene_height - size.y - 25},
        utils::adaptive_text_color(
            Settings::get_instance().get_color(Settings::num_color - 1)),
        20, 2);

    DrawRectangleRec(shape, RAYWHITE);

    if (GuiTextBox(shape, static_cast<char*>(m_text_input),
                   constants::text_buffer_size, m_is_active)) {
        m_is_active ^= 1;
    }

    options_head += shape.width;

    shape = {options_head, constants::scene_height - size.y, size.y, size.y};

    m_set_random = GuiButton(shape, "#78#");

    options_head += (shape.width + head_offset);
}

bool TextInput::interact() {
    if (m_set_random) {
        auto value = utils::get_random(m_random_min, m_random_max);
        m_set_random = false;
        std::strncpy(m_text_input, std::to_string(value).c_str(),
                     constants::text_buffer_size);
        return true;
    }

    return false;
}

core::Deque<int> TextInput::extract_values() {
    core::Deque<int> nums = utils::str_extract_data(m_text_input);  // NOLINT
    return nums;
}

}  // namespace component
