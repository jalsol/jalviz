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

        case 2: {
            m_text_input.render(options_head, head_offset);
        } break;

        default:
            utils::unreachable();
    }

    m_go |= render_go_button();
}

void ArrayScene::render() {
    core::Deque<gui::GuiArray<int, max_size>> sequence = m_sequence;
    ++m_anim_counter;

    int frame_idx = m_sequence_controller.get_run_all()
                        ? m_anim_counter * 2.0F *
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
        m_array.render();
        m_sequence_controller.set_run_all(false);
    }

    m_sequence_controller.render();
    render_options(scene_options);
}

void ArrayScene::interact() {
    if (m_sequence_controller.interact()) {
        m_anim_counter = 0;
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
    int index = m_index_input.extract_values().front();
    int value = m_text_input.extract_values().front();

    if (0 <= index && index < max_size && utils::val_in_range(value)) {
        while (!m_sequence.empty()) {
            m_sequence.pop_back();
        }

        // initial state (before update)
        m_sequence.push_back(m_array);

        // highlight
        m_array.set_color(index, ORANGE);
        m_sequence.push_back(m_array);

        // update
        m_array[index] = value;
        m_array.set_color(index, GREEN);
        m_sequence.push_back(m_array);

        // undo highlight
        m_array.set_color(index, BLACK);

        m_anim_counter = 0;
        m_sequence_controller.set_max_value((int)m_sequence.size());
        m_sequence_controller.set_run_all(true);
    }
}

void ArrayScene::interact_file_import() {
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values());

    m_file_dialog.reset_pressed();
}

void ArrayScene::interact_search() {
    int value = m_text_input.extract_values().front();

    while (!m_sequence.empty()) {
        m_sequence.pop_back();
    }

    // initial state
    m_sequence.push_back(m_array);

    for (std::size_t i = 0; i < max_size; ++i) {
        m_array.set_color(i, ORANGE);
        m_sequence.push_back(m_array);

        if (m_array[i] == value) {
            m_array.set_color(i, GREEN);
            m_sequence.push_back(m_array);
            m_array.set_color(i, BLACK);
            break;
        }

        m_array.set_color(i, BLACK);
        m_sequence.push_back(m_array);
    }

    m_anim_counter = 0;
    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_run_all(true);
}

}  // namespace scene
