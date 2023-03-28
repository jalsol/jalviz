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

// void StackScene::render() {
//     m_stack.render();
//     render_options(scene_options);
// }

void StackScene::render() {
    core::Deque<gui::GuiStack<int>> sequence = m_sequence;
    m_sequence_controller.inc_anim_counter();

    int frame_idx = m_sequence_controller.get_run_all()
                        ? m_sequence_controller.get_anim_counter() * 2.0F *
                              m_sequence_controller.get_speed_scale() /
                              constants::frames_per_second
                        : m_sequence_controller.get_progress_value();

    for (int i = 0; !sequence.empty() && i < frame_idx; ++i) {
        sequence.pop_front();
        m_sequence_controller.set_progress_value(i + 1);
    }

    if (!sequence.empty()) {
        sequence.front().render();
    } else {  // end of sequence
        m_stack.render();
        m_sequence_controller.set_run_all(false);
    }

    m_sequence_controller.render();
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
    if (m_sequence_controller.interact()) {
        m_sequence_controller.reset_anim_counter();
        return;
    }

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
            interact_push();
        } break;

        case 2: {
            interact_pop();
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

void StackScene::interact_import(core::Deque<int> nums) {
    while (!m_sequence.empty()) {
        m_sequence.pop_front();
    }

    m_stack = gui::GuiStack<int>();

    while (!nums.empty()) {
        if (utils::val_in_range(nums.back())) {
            m_stack.push(nums.back());
        }
        nums.pop_back();
    }
}

void StackScene::interact_push() {
    if (m_go && m_stack.size() < scene_options.max_size) {
        while (!m_sequence.empty()) {
            m_sequence.pop_front();
        }

        m_sequence.push_back(m_stack);

        m_stack.push(m_text_input.extract_values().front());
        m_stack.top().set_color(BLUE);
        m_sequence.push_back(m_stack);

        m_stack.top().set_color(BLACK);
        m_sequence.push_back(m_stack);

        m_sequence_controller.set_max_value((int)m_sequence.size());
        m_sequence_controller.set_rerun();
    }
}

void StackScene::interact_pop() {
    if (m_go && !m_stack.empty()) {
        while (!m_sequence.empty()) {
            m_sequence.pop_front();
        }

        m_sequence.push_back(m_stack);

        m_stack.top().set_color(RED);
        m_sequence.push_back(m_stack);

        auto old_top = m_stack.top();
        m_stack.pop();

        if (!m_stack.empty()) {
            m_stack.top().set_color(GREEN);
        }

        m_stack.push(old_top.get_value());
        m_stack.top().set_color(RED);
        m_sequence.push_back(m_stack);

        m_stack.pop();
        m_sequence.push_back(m_stack);

        if (!m_stack.empty()) {
            m_stack.top().set_color(BLACK);
            m_sequence.push_back(m_stack);
        }

        m_sequence_controller.set_max_value((int)m_sequence.size());
        m_sequence_controller.set_rerun();
    }
}

void StackScene::interact_file_import() {
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values());

    m_file_dialog.reset_pressed();
}

}  // namespace scene
