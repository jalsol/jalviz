#ifndef COMPONENT_TEXT_INPUT_HPP_
#define COMPONENT_TEXT_INPUT_HPP_

#include <string>

#include "constants.hpp"
#include "core/deque.hpp"
#include "raylib.h"

namespace component {

class TextInput {
protected:
    char m_text_input[constants::text_buffer_size] = "";  // NOLINT
    bool m_is_active{};
    const char* m_label{};

public:
    static constexpr Vector2 size{200, 50};

    TextInput() = default;
    TextInput(const char* label);

    void render(float x, float y);
    void render_head(float& options_head, float head_offset);
    std::string get_input() const;
    bool is_active() const;
    void set_input(const char* input, int len);
    void set_label(const char* const label);
    core::Deque<int> extract_values();
};

}  // namespace component

#endif  // COMPONENT_TEXT_INPUT_HPP_
