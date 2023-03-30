#include "dynamic_array_scene.hpp"

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

DynamicArrayScene& DynamicArrayScene::get_instance() {
    static DynamicArrayScene scene;
    return scene;
}

void DynamicArrayScene::render_inputs() {
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
            m_index_input.render(options_head, head_offset);
            m_text_input.render(options_head, head_offset);
        } break;

        case 2:
        case 3: {
            m_text_input.render(options_head, head_offset);
        } break;

        case 4:
            break;

        default:
            utils::unreachable();
    }

    m_go |= render_go_button();
}

void DynamicArrayScene::render() {
    m_sequence_controller.inc_anim_counter();

    int frame_idx = m_sequence_controller.get_anim_frame();
    auto* const frame_ptr = m_sequence.find(frame_idx);
    m_sequence_controller.set_progress_value(frame_idx);

    if (frame_ptr != nullptr) {
        frame_ptr->data.render();
    } else {  // end of sequence
        m_array.render();
        m_sequence_controller.set_run_all(false);
    }

    m_sequence_controller.render();
    render_options(scene_options);
}

void DynamicArrayScene::interact() {
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
            interact_update();
        } break;

        case 2: {
            interact_search();
        } break;

        case 3: {
            interact_push();
        } break;

        case 4: {
            interact_pop();
        } break;

        default:
            utils::unreachable();
    }

    m_go = false;
}

void DynamicArrayScene::interact_random() {
    m_array = {};

    for (std::size_t i = 0; i < max_size; ++i) {
        m_array[i] = utils::get_random(constants::min_val, constants::max_val);
    }
}

void DynamicArrayScene::interact_import(core::Deque<int> nums) {
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

void DynamicArrayScene::interact_update() {
    int index = m_index_input.extract_values().front();
    int value = m_text_input.extract_values().front();

    if (0 <= index && index < max_size && utils::val_in_range(value)) {
        m_sequence.clear();

        // initial state (before update)
        m_sequence.insert(m_sequence.size(), m_array);

        // highlight
        m_array.set_color(index, ORANGE);
        m_sequence.insert(m_sequence.size(), m_array);

        // update
        m_array[index] = value;
        m_array.set_color(index, GREEN);
        m_sequence.insert(m_sequence.size(), m_array);

        // undo highlight
        m_array.set_color(index, BLACK);

        m_sequence_controller.set_max_value((int)m_sequence.size());
        m_sequence_controller.set_rerun();
    }
}

void DynamicArrayScene::interact_file_import() {
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values());

    m_file_dialog.reset_pressed();
}

void DynamicArrayScene::interact_search() {
    int value = m_text_input.extract_values().front();

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_array);

    for (std::size_t i = 0; i < m_array.size(); ++i) {
        m_array.set_color(i, ORANGE);
        m_sequence.insert(m_sequence.size(), m_array);

        if (m_array[i] == value) {
            m_array.set_color(i, GREEN);
            m_sequence.insert(m_sequence.size(), m_array);
            m_array.set_color(i, BLACK);
            break;
        }

        m_array.set_color(i, BLACK);
        m_sequence.insert(m_sequence.size(), m_array);
    }

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void DynamicArrayScene::interact_push() {
    int value = m_text_input.extract_values().front();

    if (m_array.size() >= max_size) {
        return;
    }

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_array);

    if (m_array.size() == m_array.capacity()) {
        m_array.realloc(m_array.size() + 1);
        m_sequence.insert(m_sequence.size(), m_array);
    }
    m_array.set_color(m_array.size(), ORANGE);
    m_sequence.insert(m_sequence.size(), m_array);

    m_array.push(value);
    m_array.set_color(m_array.size() - 1, GREEN);
    m_sequence.insert(m_sequence.size(), m_array);

    m_array.set_color(m_array.size() - 1, BLACK);

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void DynamicArrayScene::interact_pop() {
    if (m_array.size() == 0) {
        return;
    }

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_array);

    m_array.set_color(m_array.size() - 1, ORANGE);
    m_sequence.insert(m_sequence.size(), m_array);

    m_array.pop();

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

}  // namespace scene
