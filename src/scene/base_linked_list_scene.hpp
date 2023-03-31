#ifndef SCENE_BASE_LINKED_LIST_SCENE_HPP_
#define SCENE_BASE_LINKED_LIST_SCENE_HPP_

#include "base_scene.hpp"
#include "component/code_highlighter.hpp"
#include "component/file_dialog.hpp"
#include "component/text_input.hpp"
#include "core/doubly_linked_list.hpp"
#include "gui/circular_linked_list_gui.hpp"
#include "gui/doubly_linked_list_gui.hpp"
#include "gui/linked_list_gui.hpp"
#include "raygui.h"

namespace scene {

template<typename Con>
class BaseLinkedListScene : public internal::BaseScene {
private:
    internal::SceneOptions scene_options{
        // max_size
        8,  // NOLINT

        // mode_labels
        "Mode: Create;"
        "Mode: Add;"
        "Mode: Delete;"
        "Mode: Update;"
        "Mode: Search",

        // mode_selection
        0,

        // action_labels
        {
            // Mode: Create
            "Action: Random;Action: Input;Action: File",
            // Mode: Add
            "",
            // Mode: Delete
            "",
            // Mode: Update
            "",
            // Mode: Search
            "",
        },

        // action_selection
        core::DoublyLinkedList<int>{0, 0, 0, 0, 0},
    };

    using internal::BaseScene::button_size;
    using internal::BaseScene::head_offset;
    using internal::BaseScene::options_head;

    Con m_list{
        gui::GuiNode<int>{1},
        gui::GuiNode<int>{2},
        gui::GuiNode<int>{3},
    };
    core::DoublyLinkedList<Con> m_sequence;

    bool m_go{};
    component::TextInput m_text_input;
    component::TextInput m_index_input;
    component::FileDialog m_file_dialog;
    using internal::BaseScene::m_code_highlighter;
    using internal::BaseScene::m_sequence_controller;

    BaseLinkedListScene() = default;

    using internal::BaseScene::render_go_button;
    using internal::BaseScene::render_options;
    void render_inputs() override;

    void interact_random();
    void interact_import(core::Deque<int> nums);
    void interact_file_import();

    void interact_add();
    void interact_add_head(int value);
    void interact_add_tail(int value);
    void interact_add_middle(int index, int value);

    void interact_delete();
    void interact_delete_head();
    void interact_delete_tail();
    void interact_delete_middle(int index);

    void interact_update();
    void interact_search();

public:
    BaseLinkedListScene(const BaseLinkedListScene&) = delete;
    BaseLinkedListScene(BaseLinkedListScene&&) = delete;
    BaseLinkedListScene& operator=(const BaseLinkedListScene&) = delete;
    BaseLinkedListScene& operator=(BaseLinkedListScene&&) = delete;
    ~BaseLinkedListScene() override = default;

    static BaseLinkedListScene& get_instance();

    void render() override;
    void interact() override;
};

using LinkedListScene = BaseLinkedListScene<gui::GuiLinkedList<int>>;
using DoublyLinkedListScene =
    BaseLinkedListScene<gui::GuiDoublyLinkedList<int>>;
using CircularLinkedListScene =
    BaseLinkedListScene<gui::GuiCircularLinkedList<int>>;

template<typename Con>
BaseLinkedListScene<Con>& BaseLinkedListScene<Con>::get_instance() {
    static BaseLinkedListScene scene;
    return scene;
}

template<typename Con>
void BaseLinkedListScene<Con>::render_inputs() {
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

template<typename Con>
void BaseLinkedListScene<Con>::render() {
    m_sequence_controller.inc_anim_counter();

    int frame_idx = m_sequence_controller.get_anim_frame();
    auto* const frame_ptr = m_sequence.find(frame_idx);
    m_sequence_controller.set_progress_value(frame_idx);

    if (frame_ptr != nullptr) {
        frame_ptr->data.render();
        m_code_highlighter.highlight(frame_idx);
    } else {  // end of sequence
        m_list.render();
        m_sequence_controller.set_run_all(false);
    }

    m_code_highlighter.render();
    m_sequence_controller.render();
    render_options(scene_options);
}

template<typename Con>
void BaseLinkedListScene<Con>::interact() {
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

template<typename Con>
void BaseLinkedListScene<Con>::interact_random() {
    std::size_t size =
        utils::get_random(std::size_t{1}, scene_options.max_size);
    m_list = Con();

    for (auto i = 0; i < size; ++i) {
        m_list.insert(
            i, utils::get_random(constants::min_val, constants::max_val));
    }
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_import(core::Deque<int> nums) {
    m_sequence.clear();
    m_list = Con();

    while (!nums.empty()) {
        if (utils::val_in_range(nums.front())) {
            m_list.insert(m_list.size(), nums.front());
        }
        nums.pop_front();
    }
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_file_import() {
    if (!m_file_dialog.is_pressed()) {
        return;
    }

    interact_import(m_file_dialog.extract_values());

    m_file_dialog.reset_pressed();
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_add() {
    int index = m_index_input.extract_values().front();
    int value = m_text_input.extract_values().front();

    if (!(0 <= index && index <= m_list.size())) {
        return;
    }

    if (!utils::val_in_range(value)) {
        return;
    }

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

template<typename Con>
void BaseLinkedListScene<Con>::interact_add_head(int value) {
    m_code_highlighter.set_code({
        "Node* node = new Node(value);",
        "node->next = head;",
        "head = next;",
    });
    m_code_highlighter.push_into_sequence(-1);

    m_list.insert(0, value);

    m_list.at(0).set_color(BLUE);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    if (m_list.size() > 1) {
        m_list.at(1).set_color(VIOLET);
    }

    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(1);

    if (m_list.size() > 1) {
        m_list.at(1).set_color(BLACK);
    }

    m_list.at(0).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(2);

    m_list.at(0).set_color(BLACK);
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_add_tail(int value) {
    m_code_highlighter.set_code({
        "Node* node = new Node(value);",
        "tail->next = node;",
        "tail = tail->next;",
    });
    m_code_highlighter.push_into_sequence(-1);

    std::size_t size = m_list.size();

    m_list.insert(size, value);
    m_list.at(size).set_color(BLUE);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    m_list.at(size - 1).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(1);

    m_list.at(size - 1).set_color(BLACK);
    m_list.at(size).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(2);

    m_list.at(size).set_color(BLACK);
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_add_middle(int index, int value) {
    m_code_highlighter.set_code({
        "Node* pre = head;",
        "for (i = 0; i < index - 1; ++i)",
        "    pre = pre->next;",
        "",
        "Node* nxt = pre->next;",
        "Node* node = new Node(value);",
        "node->next = nxt;",
        "pre->next = node;",
    });
    m_code_highlighter.push_into_sequence(-1);

    m_list.at(0).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    // search until index - 1
    for (int i = 0; i < index - 1; ++i) {
        m_list.at(i).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(1);

        m_list.at(i).set_color(BLACK);
        m_list.at(i + 1).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(2);
    }

    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(1);

    // reaching index - 1
    // cur
    m_list.at(index - 1).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(3);

    // cur->next
    m_list.at(index).set_color(PINK);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(4);

    // insert between cur and cur->next
    m_list.insert(index, value);
    m_list.at(index).set_color(BLUE);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(5);

    m_list.at(index - 1).set_color(ORANGE);
    m_list.at(index + 1).set_color(BLACK);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(6);

    m_list.at(index - 1).set_color(BLACK);
    m_list.at(index + 1).set_color(PINK);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(7);

    // done
    m_list.at(index - 1).set_color(BLACK);
    m_list.at(index).set_color(BLACK);
    m_list.at(index + 1).set_color(BLACK);
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_delete() {
    if (m_list.empty()) {
        return;
    }

    int index = m_index_input.extract_values().front();

    if (!(0 <= index && index < m_list.size())) {
        return;
    }

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

template<typename Con>
void BaseLinkedListScene<Con>::interact_delete_head() {
    m_code_highlighter.set_code({
        "Node* temp = head;",
        "head = head->next;",
        "delete temp;",
    });
    m_code_highlighter.push_into_sequence(-1);

    m_list.at(0).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    m_list.at(0).set_color(RED);
    if (m_list.size() > 1) {
        m_list.at(1).set_color(VIOLET);
    }
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(1);

    m_list.remove(0);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(2);

    if (m_list.size() > 0) {
        m_list.at(0).set_color(BLACK);
    }
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_delete_tail() {
    m_code_highlighter.set_code({
        "Node* pre = head;",
        "Node* nxt = pre->next;",
        "while (nxt->next != nullptr)",
        "    pre = pre->next, nxt = nxt->next;",
        "",
        "delete nxt;",
        "tail = pre;",
    });
    m_code_highlighter.push_into_sequence(-1);

    m_list.at(0).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    m_list.at(1).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(1);

    int idx = 0;
    for (; idx + 2 < m_list.size(); ++idx) {
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(2);

        m_list.at(idx).set_color(BLACK);
        m_list.at(idx + 1).set_color(ORANGE);
        m_list.at(idx + 2).set_color(GREEN);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(3);
    }

    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(2);

    m_list.at(idx).set_color(ORANGE);
    m_list.at(idx + 1).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(4);

    m_list.remove(idx + 1);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(5);

    m_list.at(idx).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(6);

    m_list.at(idx).set_color(BLACK);
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_delete_middle(int index) {
    m_code_highlighter.set_code({
        "Node* pre = head;",
        "for (i = 0; i < index - 1; i++)",
        "    pre = pre->next;",
        "",
        "Node* node = pre->next;",
        "Node* nxt = node->next;",
        "delete node;",
        "pre->next = nxt;",
    });
    m_code_highlighter.push_into_sequence(-1);

    m_list.at(0).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    int idx = 0;
    for (; idx + 1 < index; ++idx) {
        m_list.at(idx).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(1);

        m_list.at(idx).set_color(BLACK);
        m_list.at(idx + 1).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(2);
    }

    m_list.at(idx).set_color(ORANGE);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(3);

    m_list.at(idx + 1).set_color(RED);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(4);

    m_list.at(idx + 2).set_color(GREEN);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(5);

    m_list.remove(idx + 1);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(6);

    m_list.at(idx + 1).set_color(PINK);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(7);

    m_list.at(idx).set_color(BLACK);
    m_list.at(idx + 1).set_color(BLACK);
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_update() {
    int index = m_index_input.extract_values().front();
    int value = m_text_input.extract_values().front();

    if (!(0 <= index && index < m_list.size())) {
        return;
    }

    m_code_highlighter.set_code({
        "Node* node = head;",
        "for (i = 0; i < index; i++)",
        "    node = node->next;",
        "",
        "node->value = value;",
    });

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(-1);

    m_list.at(0).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    for (int i = 0; i < index; ++i) {
        m_list.at(i).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(1);

        m_list.at(i).set_color(BLACK);
        m_list.at(i + 1).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(2);
    }

    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(1);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(3);

    m_list.at(index).set_color(GREEN);
    m_list.at(index).set_value(value);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(4);

    m_list.at(index).set_color(BLACK);

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

template<typename Con>
void BaseLinkedListScene<Con>::interact_search() {
    int value = m_text_input.extract_values().front();
    if (!utils::val_in_range(value)) {
        return;
    }

    m_code_highlighter.set_code({
        "Node* node = head;",
        "while (node != nullptr) {",
        "    if (node->value == value)",
        "        return node;",
        "    node = node->next;",
        "}",
        "return not_found",
    });

    m_sequence.clear();
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(-1);

    m_list.at(0).set_color(VIOLET);
    m_sequence.insert(m_sequence.size(), m_list);
    m_code_highlighter.push_into_sequence(0);

    std::size_t idx = 0;

    while (idx < m_list.size()) {
        m_list.at(idx).set_color(ORANGE);
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(1);

        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(2);
        if (m_list.at(idx).get_value() == value) {
            m_list.at(idx).set_color(GREEN);
            m_sequence.insert(m_sequence.size(), m_list);
            m_code_highlighter.push_into_sequence(3);
            m_list.at(idx).set_color(BLACK);
            break;
        }

        m_list.at(idx).set_color(BLACK);
        ++idx;
        if (idx < m_list.size()) {
            m_list.at(idx).set_color(ORANGE);
        }
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(4);
    }

    if (idx >= m_list.size()) {
        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(1);

        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(5);

        m_sequence.insert(m_sequence.size(), m_list);
        m_code_highlighter.push_into_sequence(6);
    }

    m_sequence_controller.set_max_value((int)m_sequence.size());
    m_sequence_controller.set_rerun();
}

}  // namespace scene

#endif  // SCENE_BASE_LINKED_LIST_SCENE_HPP_
