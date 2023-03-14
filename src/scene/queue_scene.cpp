#include "queue_scene.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include "constants.hpp"
#include "raygui.h"
#include "utils.hpp"

namespace scene {

QueueScene& QueueScene::get_instance() {
    static QueueScene scene;
    return scene;
}

void QueueScene::render_options() {
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

void QueueScene::render_inputs() {
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
            render_text_input();
        } break;

        case 2:
            break;
        default:
            utils::unreachable();
    }

    m_go |= render_go_button();
}

bool QueueScene::render_go_button() const {
    return GuiButton(Rectangle{static_cast<float>(options_head),
                               constants::scene_height - button_size.y,
                               button_size.y, button_size.y},
                     "Go");
}

void QueueScene::render_text_input() {
    GuiTextBox(Rectangle{static_cast<float>(options_head),
                         constants::scene_height - button_size.y, button_size.x,
                         button_size.y},
               static_cast<char*>(m_text_input), button_size.y, true);

    options_head += (button_size.x + head_offset);
}

void QueueScene::render_file_input() {
    if (m_file_dialog_state.windowActive) {
        GuiLock();
    }

    if (GuiButton(Rectangle{static_cast<float>(options_head),
                            constants::scene_height - button_size.y,
                            button_size.x, button_size.y},
                  GuiIconText(ICON_FILE_OPEN, "Select file"))) {
        m_file_dialog_state.windowActive = true;
    }

    options_head += (button_size.x + head_offset);

    GuiUnlock();
    GuiFileDialog(&m_file_dialog_state);
}

void QueueScene::render() {
    m_queue.render();
    render_options();
}

void QueueScene::interact() {
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
                    interact_import(true, max_size);
                } break;

                case 2: {
                    interact_file_import();
                } break;

                default:
                    utils::unreachable();
            }
        } break;

        case 1: {
            if (m_go && m_queue.size() < max_size) {
                interact_import(false, 1);
            }
        } break;

        case 2: {
            if (m_go && !m_queue.empty()) {
                m_queue.pop();
            }
        } break;

        default:
            utils::unreachable();
    }

    m_go = false;
}

void QueueScene::interact_random() {
    std::size_t size = utils::get_random(std::size_t{1}, max_size);
    m_queue = gui::GuiQueue<int>();

    for (auto i = 0; i < size; ++i) {
        m_queue.push(utils::get_random(constants::min_val, constants::max_val));
    }
}

void QueueScene::interact_import(bool clear, int amount_to_take) {
    core::Deque<int> nums = utils::str_extract_data(m_text_input);  // NOLINT
    m_text_input[0] = '\0';

    if (clear) {
        m_queue = gui::GuiQueue<int>();
    }

    while (!nums.empty() && amount_to_take > 0) {
        if (utils::val_in_range(nums.front())) {
            m_queue.push(nums.front());
        }
        nums.pop_front();
        --amount_to_take;
    }
}

void QueueScene::interact_file_import() {
    if (!m_file_dialog_state.SelectFilePressed) {
        return;
    }

    std::string file_name;
    file_name += static_cast<char*>(m_file_dialog_state.dirPathText);
    file_name += '/';
    file_name += static_cast<char*>(m_file_dialog_state.fileNameText);

    std::ifstream ifs(file_name);
    ifs >> m_text_input;

    interact_import(true, max_size);

    m_file_dialog_state.SelectFilePressed = false;
}

}  // namespace scene
