#include "array_scene.hpp"

#include <cstddef>
// #include <cstdlib>
// #include <cstring>
#include <fstream>
// #include <iostream>
// #include <limits>
// #include <string>

#include "constants.hpp"
#include "raygui.h"
#include "utils.hpp"

namespace scene {

ArrayScene& ArrayScene::get_instance() {
    static ArrayScene scene;
    return scene;
}

void ArrayScene::render_options() {
    options_head = 2 * constants::sidebar_width;

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

void ArrayScene::render_inputs() {
    switch (m_mode_selection) {
        case 0: {
            switch (m_action_selection.at(m_mode_selection)) {
                case 0:
                    break;
                case 1: {
                    m_text_input.render(options_head, head_offset);
                } break;
                case 2: {
                    m_file_dialog.render(options_head, head_offset);
                } break;
                default:
                    utils::unreachable();
            }
        } break;

        case 1: {
            m_index_input.render(options_head, head_offset);
            m_text_input.render(options_head, head_offset);
        } break;

        case 2:
            break;
        default:
            utils::unreachable();
    }

    m_go |= render_go_button();
}

bool ArrayScene::render_go_button() const {
    return GuiButton(Rectangle{static_cast<float>(options_head),
                               constants::scene_height - button_size.y,
                               button_size.y, button_size.y},
                     "Go");
}

void ArrayScene::render() {
    m_array.render();
    render_options();
}

void ArrayScene::interact() {
    if (!m_go) {
        return;
    }

    switch (m_mode_selection) {
        case 0: {
            switch (m_action_selection.at(m_mode_selection)) {
                case 0: {
                    interact_random();
                } break;

                case 1: {
                    interact_import(m_text_input.extract_values());
                } break;

                case 2: {
                    interact_file_import();
                } break;

                default:
                    utils::unreachable();
            }
        } break;

        case 1: {
            interact_update();
        } break;

        case 2: {
            // if (m_go && !m_array.empty()) {
            //     m_array.pop();
            // }
        } break;

        default:
            utils::unreachable();
    }

    m_go = false;
}

void ArrayScene::interact_random() {
    m_array = {};

    for (std::size_t i = 0; i < max_size; ++i) {
        m_array[i] = utils::get_random(constants::min_val, constants::max_val);
    }
}

void ArrayScene::interact_import(core::Deque<int> nums) {
    m_array = {};
    std::size_t i;  // NOLINT

    for (i = 0; i < max_size && !nums.empty(); ++i) {
        m_array[i] = nums.front();
        nums.pop_front();
    }

    for (; i < max_size; ++i) {
        m_array[i] = 0;
    }
}

void ArrayScene::interact_update() {
    int index = m_index_input.extract_values().front();
    int value = m_text_input.extract_values().front();

    if (0 <= index && index < max_size && utils::val_in_range(value)) {
        m_array[index] = value;
    }
}

void ArrayScene::interact_file_import() {
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values());

    m_file_dialog.reset_pressed();
}

}  // namespace scene
