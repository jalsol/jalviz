#ifndef COMPONENT_TEXT_INPUT_HPP_
#define COMPONENT_TEXT_INPUT_HPP_

#include <string>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raylib.h"

namespace component {

class TextInput {
private:
    char m_text_input[constants::text_buffer_size] = "";  // NOLINT
    bool m_is_active{};
    const char* m_label{};

    int m_random_min{constants::min_val};
    int m_random_max{constants::max_val};
    bool m_set_random{};

public:
    static constexpr Vector2 size{200, 50};

    TextInput() = default;
    TextInput(const char* label);

    void render(float& options_head, float head_offset);
    bool interact();
    core::Deque<int> extract_values();
    void set_random_min(int value);
    void set_random_max(int value);
};

}  // namespace component

#endif  // COMPONENT_TEXT_INPUT_HPP_
