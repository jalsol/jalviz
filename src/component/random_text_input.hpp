#ifndef COMPONENT_RANDOM_TEXT_INPUT_HPP_
#define COMPONENT_RANDOM_TEXT_INPUT_HPP_

#include <string>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raylib.h"
#include "text_input.hpp"

namespace component {

class RandomTextInput : public TextInput {
private:
    int m_random_min{constants::min_val};
    int m_random_max{constants::max_val};
    bool m_set_random{};

public:
    using TextInput::size;

    RandomTextInput() = default;
    RandomTextInput(const char* label);

    using TextInput::extract_values;

    void render_head(float& options_head, float head_offset);
    bool interact();
    void set_random_min(int value);
    void set_random_max(int value);
};

}  // namespace component

#endif  // COMPONENT_RANDOM_TEXT_INPUT_HPP_
