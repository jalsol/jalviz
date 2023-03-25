#include "stack_scene.hpp"

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

StackScene& StackScene::get_instance() {
    static StackScene scene;
    return scene;
}

void StackScene::render() {
    m_stack.render();
    render_options(scene_options);
}

void StackScene::render_inputs() {
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

void StackScene::interact() {
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
            if (m_go && m_stack.size() < scene_options.max_size) {
                interact_import(m_text_input.extract_values(), false, 1);
            }
        } break;

        case 2: {
            if (m_go && !m_stack.empty()) {
                m_stack.pop();
            }
        } break;

        default:
            utils::unreachable();
    }

    m_go = false;
}

void StackScene::interact_random() {
    std::size_t size =
        utils::get_random(std::size_t{1}, scene_options.max_size);
    m_stack = gui::GuiStack<int>();

    for (auto i = 0; i < size; ++i) {
        m_stack.push(utils::get_random(constants::min_val, constants::max_val));
    }
}

void StackScene::interact_import(core::Deque<int> nums, bool clear,
                                 std::size_t amount_to_take) {
    if (clear) {
        m_stack = gui::GuiStack<int>();
    }

    while (!nums.empty() && amount_to_take > 0) {
        if (utils::val_in_range(nums.back())) {
            m_stack.push(nums.back());
        }
        nums.pop_back();
        --amount_to_take;
    }
}

void StackScene::interact_file_import() {
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values(), true,
                    scene_options.max_size);

    m_file_dialog.reset_pressed();
}

}  // namespace scene
