#ifndef SCENE_DOUBLY_LINKED_LIST_SCENE_HPP_
#define SCENE_DOUBLY_LINKED_LIST_SCENE_HPP_

#include "base_scene.hpp"
#include "component/file_dialog.hpp"
#include "component/text_input.hpp"
#include "core/doubly_linked_list.hpp"
#include "gui/doubly_linked_list_gui.hpp"
#include "raygui.h"

namespace scene {

class DoublyLinkedListScene : public internal::BaseScene {
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

    gui::GuiDoublyLinkedList<int> m_list{
        gui::GuiNode<int>{1},
        gui::GuiNode<int>{2},
        gui::GuiNode<int>{3},
    };
    core::DoublyLinkedList<gui::GuiDoublyLinkedList<int>> m_sequence;

    bool m_go{};
    component::TextInput m_text_input;
    component::TextInput m_index_input;
    component::FileDialog m_file_dialog;
    using internal::BaseScene::m_code_highlighter;
    using internal::BaseScene::m_sequence_controller;

    DoublyLinkedListScene() = default;

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
    DoublyLinkedListScene(const DoublyLinkedListScene&) = delete;
    DoublyLinkedListScene(DoublyLinkedListScene&&) = delete;
    DoublyLinkedListScene& operator=(const DoublyLinkedListScene&) = delete;
    DoublyLinkedListScene& operator=(DoublyLinkedListScene&&) = delete;
    ~DoublyLinkedListScene() override = default;

    static DoublyLinkedListScene& get_instance();

    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_DOUBLY_LINKED_LIST_SCENE_HPP_
