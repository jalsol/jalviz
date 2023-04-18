#ifndef SCENE_DYNAMIC_ARRAY_SCENE_HPP_
#define SCENE_DYNAMIC_ARRAY_SCENE_HPP_

#include <array>
#include <cstddef>

#include "base_scene.hpp"
#include "component/file_dialog.hpp"
#include "constants.hpp"
#include "core/doubly_linked_list.hpp"
#include "gui/dynamic_array_gui.hpp"
#include "raygui.h"
#include "raylib.h"

namespace scene {

class DynamicArrayScene : public internal::BaseScene {
private:
    static constexpr std::size_t max_size = 8;

    internal::SceneOptions scene_options{
        // max_size
        max_size,

        // mode_labels
        "Mode: Create;"
        "Mode: Update;"
        "Mode: Search;"
        "Mode: Push;"
        "Mode: Pop",

        // mode_selection
        0,

        // action_labels
        {
            // Mode: Create
            "Action: Random;Action: Input;Action: File",

            // Mode: Update
            "",

            // Mode: Search
            "",

            // Mode: Push
            "",

            // Mode: Pop
            "",
        },

        // action_selection
        core::DoublyLinkedList<int>{0, 0, 0, 0, 0},
    };

    using internal::BaseScene::button_size;
    using internal::BaseScene::head_offset;
    using internal::BaseScene::options_head;

    gui::GuiDynamicArray<int> m_array{};
    core::DoublyLinkedList<gui::GuiDynamicArray<int>> m_sequence;

    bool m_go{};
    using internal::BaseScene::m_file_dialog;
    using internal::BaseScene::m_index_input;
    using internal::BaseScene::m_sequence_controller;
    using internal::BaseScene::m_text_input;

    using internal::BaseScene::render_go_button;
    using internal::BaseScene::render_options;
    void render_inputs() override;

    void interact_random();
    void interact_import(core::Deque<int> nums);
    void interact_file_import();
    void interact_update();
    void interact_search();
    void interact_push();
    void interact_pop();

public:
    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_DYNAMIC_ARRAY_SCENE_HPP_
