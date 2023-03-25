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
                    render_text_input();
                } break;
                case 2: {
                    render_file_input();
                } break;
                default:
                    utils::unreachable();
            }
        } break;

        case 1: {
            render_index_input();
            render_text_input();
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

void ArrayScene::render_text_input() {
    static bool locked = false;
    if (GuiTextBox(Rectangle{static_cast<float>(options_head),
                             constants::scene_height - button_size.y,
                             button_size.x, button_size.y},
                   static_cast<char*>(m_text_input), button_size.y, locked)) {
        locked ^= 1;
    }

    options_head += (button_size.x + head_offset);
}

void ArrayScene::render_index_input() {
    static bool locked = false;
    if (GuiTextBox(Rectangle{static_cast<float>(options_head),
                             constants::scene_height - button_size.y,
                             button_size.x, button_size.y},
                   static_cast<char*>(m_index_input), button_size.y, locked)) {
        locked ^= 1;
    }

    options_head += (button_size.x + head_offset);
}

void ArrayScene::render_file_input() {
    if (m_file_dialog_state.windowActive) {
        GuiLock();
    }

    const char* const file_name =
        static_cast<char*>(m_file_dialog_state.fileNameText);

    const char* const text =
        (m_file_dialog_state.SelectFilePressed) ? file_name : "Select file";

    if (GuiButton(Rectangle{static_cast<float>(options_head),
                            constants::scene_height - button_size.y,
                            button_size.x, button_size.y},
                  GuiIconText(ICON_FILE_OPEN, text))) {
        m_file_dialog_state.windowActive = true;
    }

    options_head += (button_size.x + head_offset);

    GuiUnlock();
    GuiFileDialog(&m_file_dialog_state);
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
                    interact_update();
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

void ArrayScene::interact_import() {
    core::Deque<int> nums = utils::str_extract_data(m_text_input);  // NOLINT
    m_text_input[0] = '\0';

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
    int value = utils::str_extract_data(m_text_input).front();  // NOLINT
    m_text_input[0] = '\0';

    int index = utils::str_extract_data(m_index_input).front();  // NOLINT
    m_index_input[0] = '\0';

    if (0 <= index && index < max_size && utils::val_in_range(value)) {
        m_array[index] = value;
    }
}

void ArrayScene::interact_file_import() {
    if (!m_file_dialog_state.SelectFilePressed) {
        return;
    }

    std::string file_name;
    file_name += static_cast<char*>(m_file_dialog_state.dirPathText);
    file_name += '/';
    file_name += static_cast<char*>(m_file_dialog_state.fileNameText);

    std::ifstream ifs(file_name);
    ifs >> m_text_input;

    interact_import();

    m_file_dialog_state.SelectFilePressed = false;
}

}  // namespace scene
