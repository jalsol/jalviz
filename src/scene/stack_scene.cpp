#include "stack_scene.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "constants.hpp"
#include "raygui.h"

namespace scene {

void StackScene::render_options() {
    options_head = 0;

    Rectangle mode_button_shape{static_cast<float>(options_head),
                                constants::scene_height - button_size.y,
                                button_size.x, button_size.y};
    options_head += (button_size.x + head_offset);

    m_mode_selection =
        GuiComboBox(mode_button_shape, mode_labels, m_mode_selection);

    if (std::strlen(action_labels.at(m_mode_selection)) != 0) {
        Rectangle action_button_shape{static_cast<float>(options_head),
                                      constants::scene_height - button_size.y,
                                      button_size.x, button_size.y};
        options_head += (button_size.x + head_offset);

        m_action_selection.at(m_mode_selection) =
            GuiComboBox(action_button_shape, action_labels.at(m_mode_selection),
                        m_action_selection.at(m_mode_selection));
    }

    render_inputs();
}

void StackScene::render_inputs() {
    switch (m_mode_selection) {
        case 0: {
            switch (m_action_selection.at(m_mode_selection)) {
                case 0:
                    break;
                case 1: {
                    (void)render_text_input();
                } break;
                case 2: {
                } break;
                default:
                    __builtin_unreachable();
            }
        } break;

        case 1: {
            (void)render_text_input();
        } break;
        case 2:
        case 3:
            break;
        default:
            __builtin_unreachable();
    }

    m_go |= render_go_button();
}

bool StackScene::render_go_button() const {
    return GuiButton(Rectangle{static_cast<float>(options_head),
                               constants::scene_height - button_size.y,
                               button_size.y, button_size.y},
                     "Go");
}

void StackScene::render_text_input() {
    (void)GuiTextBox(Rectangle{static_cast<float>(options_head),
                               constants::scene_height - button_size.y,
                               button_size.x, button_size.y},
                     static_cast<char*>(m_text_input), button_size.y, true);

    options_head += (button_size.x + head_offset);
}

void StackScene::render() {
    m_stack.render();
    render_options();
}

void StackScene::interact() {
    if (!m_go) {
        return;
    }

    switch (m_mode_selection) {
        case 0: {
            switch (m_action_selection.at(m_mode_selection)) {
                case 0: {
                    interact_random();
                } break;
                case 1:
                case 2: {
                } break;
                default:
                    __builtin_unreachable();
            }
        } break;

        case 1: {
            if (m_go && m_stack.size() < max_size) {
                constexpr int base = 10;
                int num = static_cast<int>(std::strtol(
                    static_cast<char*>(m_text_input), nullptr, base));
                m_stack.push(gui::Node<int>{num});
                m_text_input[0] = '\0';
            }
        } break;

        case 2: {
            if (m_go && !m_stack.empty()) {
                m_stack.pop();
            }
        } break;
        case 3:
            break;
        default:
            __builtin_unreachable();
    }

    m_go = false;
}

void StackScene::interact_random() {
    std::size_t size = utils::get_random(std::size_t{1}, max_size);
    m_stack = gui::Stack<int>();

    for (auto i = 0; i < size; ++i) {
        m_stack.push(gui::Node<int>{
            utils::get_random(constants::min_val, constants::max_val)});
    }
}

}  // namespace scene
