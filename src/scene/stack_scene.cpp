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

void StackScene::render() {
    m_sequence_controller.inc_anim_counter();

    int frame_idx = m_sequence_controller.get_anim_frame();
    auto* const frame_ptr = m_sequence.find(frame_idx);
    m_sequence_controller.set_progress_value(frame_idx);

    if (frame_ptr != nullptr) {
        frame_ptr->data.render();
        m_code_highlighter.highlight(frame_idx);
    } else {  // end of sequence
        m_stack.render();
        m_sequence_controller.set_run_all(false);
    }

    m_code_highlighter.render();
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
                    m_go = (m_file_dialog.render_head(options_head,
                                                      head_offset) > 0);
                    return;
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
    m_stack.init_label();
}

void StackScene::interact_import(core::Deque<int> nums) {
    m_sequence.clear();
    m_stack = gui::GuiStack<int>();

    while (!nums.empty()) {
        if (utils::val_in_range(nums.back())) {
            m_stack.push(nums.back());
        }
        nums.pop_back();
    }
    m_stack.init_label();
}

void StackScene::interact_push() {
    auto value_container = m_text_input.extract_values();
    if (value_container.empty()) {
        return;
    }

    int value = value_container.front();

    if (m_stack.size() >= scene_options.max_size) {
        return;
    }

    m_code_highlighter.set_code({
        "Node* node = new Node(value);",
        "node->next = head;",
        "head = node;",
    });

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(-1);

    m_stack.push(value);
    m_stack.top().set_color_index(7);
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(0);

    m_stack.pop();
    if (!m_stack.empty()) {
        m_stack.top().set_color_index(5);
    }
    m_stack.push(value);
    m_stack.top().set_color_index(7);
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(1);

    m_stack.pop();
    if (!m_stack.empty()) {
        m_stack.top().set_color_index(0);
        m_stack.top().set_label("");
    }
    m_stack.push(value);
    m_stack.top().set_color_index(4);
    m_stack.init_label();
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(2);

    m_stack.top().set_color_index(0);

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void StackScene::interact_pop() {
    if (m_stack.empty()) {
        return;
    }

    m_code_highlighter.set_code({
        "Node* temp = head;",
        "head = head->next;",
        "delete temp;",
    });

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(-1);

    m_stack.top().set_color_index(6);
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(0);

    auto old_top = m_stack.top();
    m_stack.pop();

    if (!m_stack.empty()) {
        m_stack.top().set_color_index(4);
        m_stack.top().set_label("head");
    }

    m_stack.push(old_top.get_value());
    m_stack.top().set_color_index(6);
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(1);

    m_stack.pop();
    m_sequence.insert(m_sequence.size(), m_stack);
    m_code_highlighter.push_into_sequence(2);

    if (!m_stack.empty()) {
        m_stack.top().set_color_index(0);
    }

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void StackScene::interact_file_import() {
    interact_import(m_file_dialog.extract_values());
}

}  // namespace scene
