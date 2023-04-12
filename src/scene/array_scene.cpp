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

void ArrayScene::render_inputs() {
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
            m_index_input.render(options_head, head_offset);
            m_text_input.render(options_head, head_offset);
        } break;

        case 2: {
            m_text_input.render(options_head, head_offset);
        } break;

        default:
            utils::unreachable();
    }

    m_go |= render_go_button();
}

void ArrayScene::render() {
    m_sequence_controller.inc_anim_counter();

    int frame_idx = m_sequence_controller.get_anim_frame();
    auto* const frame_ptr = m_sequence.find(frame_idx);
    m_sequence_controller.set_progress_value(frame_idx);

    if (frame_ptr != nullptr) {
        frame_ptr->data.render();
        m_code_highlighter.highlight(frame_idx);
    } else {  // end of sequence
        m_array.render();
        m_sequence_controller.set_run_all(false);
    }

    m_code_highlighter.render();
    m_sequence_controller.render();
    render_options(scene_options);
}

void ArrayScene::interact() {
    if (m_sequence_controller.interact()) {
        m_sequence_controller.reset_anim_counter();
        return;
    }

    m_index_input.set_random_max(max_size);

    if (m_text_input.interact() || m_index_input.interact()) {
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
            interact_update();
        } break;

        case 2: {
            interact_search();
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
    auto index_container = m_index_input.extract_values();
    if (index_container.empty()) {
        return;
    }

    auto value_container = m_text_input.extract_values();
    if (value_container.empty()) {
        return;
    }

    int index = index_container.front();
    int value = value_container.front();

    if (!(0 <= index && index < max_size) || !utils::val_in_range(value)) {
        return;
    }

    m_code_highlighter.set_code({
        "array[index] = value;",
    });

    m_sequence.clear();

    // initial state (before update)
    m_sequence.insert(m_sequence.size(), m_array);
    m_code_highlighter.push_into_sequence(-1);

    // highlight
    m_array.set_color_index(index, 3);
    m_sequence.insert(m_sequence.size(), m_array);
    m_code_highlighter.push_into_sequence(0);

    // update
    m_array[index] = value;
    m_array.set_color_index(index, 4);
    m_sequence.insert(m_sequence.size(), m_array);
    m_code_highlighter.push_into_sequence(0);

    // undo highlight
    m_array.set_color_index(index, 0);

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void ArrayScene::interact_file_import() {
    interact_import(m_file_dialog.extract_values());
}

void ArrayScene::interact_search() {
    auto value_container = m_text_input.extract_values();
    if (value_container.empty()) {
        return;
    }

    int value = value_container.front();
    if (!utils::val_in_range(value)) {
        return;
    }

    m_code_highlighter.set_code({
        "for (i = 0; i < size; i++)",
        "    if (array[i] == value)",
        "        return i;",
        "return not_found",
    });

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_array);
    m_code_highlighter.push_into_sequence(0);

    bool found = false;

    for (std::size_t i = 0; i < max_size; ++i) {
        m_array.set_color_index(i, 3);
        m_sequence.insert(m_sequence.size(), m_array);
        m_code_highlighter.push_into_sequence(1);

        if (m_array[i] == value) {
            found = true;
            m_array.set_color_index(i, 4);
            m_sequence.insert(m_sequence.size(), m_array);
            m_code_highlighter.push_into_sequence(2);
            m_array.set_color_index(i, 0);
            break;
        }

        m_array.set_color_index(i, 0);
        m_sequence.insert(m_sequence.size(), m_array);
        m_code_highlighter.push_into_sequence(0);
    }

    if (!found) {
        m_sequence.insert(m_sequence.size(), m_array);
        m_code_highlighter.push_into_sequence(3);
    }

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

}  // namespace scene
