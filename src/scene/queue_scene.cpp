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

void QueueScene::render_inputs() {
    int& mode = scene_options.mode_selection;

    switch (mode) {
        case 0: {
            switch (scene_options.action_selection.at(mode)) {
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
            m_text_input.render(options_head, head_offset);
        } break;

        case 2:
            break;
        default:
            utils::unreachable();
    }

    m_go |= render_go_button();
}

void QueueScene::render() {
    m_queue.render();
    render_options(scene_options);
}

void QueueScene::interact() {
    if (!m_go) {
        return;
    }

    int& mode = scene_options.mode_selection;

    switch (mode) {
        case 0: {
            switch (scene_options.action_selection.at(mode)) {
                case 0: {
                    interact_random();
                } break;

                case 1: {
                    interact_import(m_text_input.extract_values(), true,
                                    scene_options.max_size);
                } break;

                case 2: {
                    interact_file_import();
                } break;

                default:
                    utils::unreachable();
            }
        } break;

        case 1: {
            if (m_go && m_queue.size() < scene_options.max_size) {
                interact_import(m_text_input.extract_values(), false, 1);
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
    std::size_t size =
        utils::get_random(std::size_t{1}, scene_options.max_size);
    m_queue = gui::GuiQueue<int>();

    for (auto i = 0; i < size; ++i) {
        m_queue.push(utils::get_random(constants::min_val, constants::max_val));
    }
}

void QueueScene::interact_import(core::Deque<int> nums, bool clear,
                                 std::size_t amount_to_take) {
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
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values(), true,
                    scene_options.max_size);

    m_file_dialog.reset_pressed();
}

}  // namespace scene
