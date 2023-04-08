#include "text_input.hpp"

#include <cstring>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raygui.h"
#include "utils.hpp"

namespace component {

TextInput::TextInput(const char* label) : m_label{label} {}

void TextInput::render(float& options_head, float head_offset) {
    Rectangle shape{options_head, constants::scene_height - size.y, size.x,
                    size.y};

    utils::DrawText(m_label,
                    {options_head, constants::scene_height - size.y - 25},
                    BLACK, 20, 2);

    if (GuiTextBox(shape, static_cast<char*>(m_text_input),
                   constants::text_buffer_size, m_is_active)) {
        m_is_active ^= 1;
    }

    options_head += (size.x + head_offset);
}

core::Deque<int> TextInput::extract_values() {
    core::Deque<int> nums = utils::str_extract_data(m_text_input);  // NOLINT
    return nums;
}

}  // namespace component
