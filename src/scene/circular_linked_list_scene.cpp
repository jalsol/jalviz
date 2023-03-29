#include "circular_linked_list_scene.hpp"

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

CircularLinkedListScene& CircularLinkedListScene::get_instance() {
    static CircularLinkedListScene scene;
    return scene;
}

void CircularLinkedListScene::render_inputs() {
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
            m_index_input.render(options_head, head_offset);
        } break;

        case 3: {
            m_index_input.render(options_head, head_offset);
            m_text_input.render(options_head, head_offset);
        } break;

        case 4: {
            m_text_input.render(options_head, head_offset);
        } break;

        default:
            utils::unreachable();
    }

    m_go |= render_go_button();
}

void CircularLinkedListScene::render() {
    m_sequence_controller.inc_anim_counter();

    int frame_idx = m_sequence_controller.get_anim_frame();
    auto* const frame_ptr = m_sequence.find(frame_idx);
    m_sequence_controller.set_progress_value(frame_idx);

    if (frame_ptr != nullptr) {
        frame_ptr->data.render();
    } else {  // end of sequence
        m_list.render();
        m_sequence_controller.set_run_all(false);
    }

    m_sequence_controller.render();
    render_options(scene_options);
}

void CircularLinkedListScene::interact() {
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
            interact_add();
        } break;

        case 2: {
            interact_delete();
        } break;

        case 3: {
            interact_update();
        } break;

        case 4: {
            interact_search();
        } break;

        default:
            utils::unreachable();
    }

    m_go = false;
}

void CircularLinkedListScene::interact_random() {
    std::size_t size =
        utils::get_random(std::size_t{1}, scene_options.max_size);
    m_list = gui::GuiCircularLinkedList<int>();

    for (auto i = 0; i < size; ++i) {
        m_list.insert(
            i, utils::get_random(constants::min_val, constants::max_val));
    }
}

void CircularLinkedListScene::interact_import(core::Deque<int> nums) {
    m_sequence.clear();
    m_list = gui::GuiCircularLinkedList<int>();

    while (!nums.empty()) {
        if (utils::val_in_range(nums.front())) {
            m_list.insert(m_list.size(), nums.front());
        }
        nums.pop_front();
    }
}

void CircularLinkedListScene::interact_file_import() {
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values());

    m_file_dialog.reset_pressed();
}

void CircularLinkedListScene::interact_add() {
    int index = m_index_input.extract_values().front();
    int value = m_text_input.extract_values().front();

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_list);

    if (index == 0) {
        interact_add_head(value);
    } else if (index == m_list.size()) {
        interact_add_tail(value);
    } else {
        interact_add_middle(index, value);
    }

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void CircularLinkedListScene::interact_add_head(int value) {
    m_list.insert(0, value);

    m_list.at(0).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(0).set_color(BLACK);
    m_sequence.insert(m_sequence.size(), m_list);
}

void CircularLinkedListScene::interact_add_tail(int value) {
    std::size_t size = m_list.size();
    m_list.at(size - 1).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.insert(size, value);
    m_list.at(size).set_color(BLUE);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(size - 1).set_color(BLACK);
    m_list.at(size).set_color(BLACK);
}

void CircularLinkedListScene::interact_add_middle(int index, int value) {
    if (!(0 <= index && index < m_list.size())) {
        return;
    }

    // search until index - 1
    for (int i = 0; i < index - 1; ++i) {
        m_list.at(i).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);

        m_list.at(i).set_color(BLACK);
        m_sequence.insert(m_sequence.size(), m_list);
    }

    // reaching index - 1
    // cur
    m_list.at(index - 1).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);

    // cur->next
    m_list.at(index).set_color(BLUE);
    m_sequence.insert(m_sequence.size(), m_list);

    // insert between cur and cur->next
    m_list.insert(index, value);
    m_list.at(index).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);

    // done
    m_list.at(index - 1).set_color(BLACK);
    m_list.at(index).set_color(BLACK);
    m_list.at(index + 1).set_color(BLACK);
}

void CircularLinkedListScene::interact_delete() {
    if (m_list.empty()) {
        return;
    }

    int index = m_index_input.extract_values().front();

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_list);

    if (index == 0) {
        interact_delete_head();
    } else if (index + 1 == m_list.size()) {
        interact_delete_tail();
    } else {
        interact_delete_middle(index);
    }

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void CircularLinkedListScene::interact_delete_head() {
    m_list.at(0).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);

    if (m_list.size() > 1) {
        m_list.at(1).set_color(GREEN);
        m_sequence.insert(m_sequence.size(), m_list);
    }

    m_list.remove(0);
    m_sequence.insert(m_sequence.size(), m_list);

    if (m_list.size() > 0) {
        m_list.at(0).set_color(BLACK);
    }
}

void CircularLinkedListScene::interact_delete_tail() {
    int idx = 0;
    for (; idx + 2 < m_list.size(); ++idx) {
        m_list.at(idx).set_color(ORANGE);
        m_list.at(idx + 1).set_color(GREEN);

        m_sequence.insert(m_sequence.size(), m_list);

        m_list.at(idx).set_color(BLACK);
        m_list.at(idx + 1).set_color(BLACK);
    }

    m_list.at(idx).set_color(ORANGE);
    m_list.at(idx + 1).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.remove(idx + 1);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(idx).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(idx).set_color(BLACK);
}

void CircularLinkedListScene::interact_delete_middle(int index) {
    if (!(0 <= index && index < m_list.size())) {
        return;
    }

    int idx = 0;
    for (; idx + 1 < index; ++idx) {
        m_list.at(idx).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_list.at(idx).set_color(BLACK);
    }

    m_list.at(idx).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(idx + 1).set_color(RED);
    m_list.at(idx + 2).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.remove(idx + 1);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(idx).set_color(BLACK);
    m_list.at(idx + 1).set_color(BLACK);
}

void CircularLinkedListScene::interact_update() {
    int index = m_index_input.extract_values().front();
    int value = m_text_input.extract_values().front();

    if (!(0 <= index && index < m_list.size())) {
        return;
    }

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_list);

    for (int i = 0; i < index; ++i) {
        m_list.at(i).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_list.at(i).set_color(BLACK);
    }

    m_list.at(index).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(index).set_color(GREEN);
    m_list.at(index).set_value(value);
    m_sequence.insert(m_sequence.size(), m_list);

    m_list.at(index).set_color(BLACK);

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

void CircularLinkedListScene::interact_search() {
    int value = m_text_input.extract_values().front();

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_list);

    int idx = 0;
    for (; idx < m_list.size(); ++idx) {
        if (m_list.at(idx).get_value() == value) {
            break;
        }

        m_list.at(idx).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_list.at(idx).set_color(BLACK);
    }

    if (idx < m_list.size()) {
        m_list.at(idx).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);

        m_list.at(idx).set_color(GREEN);
        m_sequence.insert(m_sequence.size(), m_list);

        m_list.at(idx).set_color(BLACK);
    }

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

}  // namespace scene
