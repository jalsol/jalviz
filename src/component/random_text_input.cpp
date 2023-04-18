#include "random_text_input.hpp"

#include <cstring>
#include <iostream>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raygui.h"
#include "settings.hpp"
#include "utils.hpp"

namespace component {

RandomTextInput::RandomTextInput(const char* label) : TextInput{label} {}

void RandomTextInput::set_random_min(int value) { m_random_min = value; }

void RandomTextInput::set_random_max(int value) { m_random_max = value; }

void RandomTextInput::render_head(float& options_head, float head_offset) {
    TextInput::render_head(options_head, 0);

    Rectangle shape = {options_head, constants::scene_height - size.y, size.y,
                       size.y};
    m_set_random = GuiButton(shape, "#78#");

    options_head += (shape.width + head_offset);
}

bool RandomTextInput::interact() {
    if (m_set_random) {
        auto value = utils::get_random(m_random_min, m_random_max);
        m_set_random = false;
        std::strncpy(m_text_input, std::to_string(value).c_str(),
                     constants::text_buffer_size);
        return true;
    }

    return false;
}

}  // namespace component
