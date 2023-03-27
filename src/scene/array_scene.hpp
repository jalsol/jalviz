#ifndef SCENE_ARRAY_SCENE_HPP_
#define SCENE_ARRAY_SCENE_HPP_

#include <array>
#include <cstddef>

#include "base_scene.hpp"
#include "component/file_dialog.hpp"
#include "component/sequence_controller.hpp"
#include "component/text_input.hpp"
#include "constants.hpp"
#include "gui/array_gui.hpp"
#include "raygui.h"
#include "raylib.h"

namespace scene {

class ArrayScene : public internal::BaseScene {
private:
    static constexpr std::size_t max_size = 8;

    internal::SceneOptions scene_options{
        // max_size
        max_size,

        // mode_labels
        "Mode: Create;"
        "Mode: Update;"
        "Mode: Search",

        // mode_selection
        0,

        // action_labels
        {
            // Mode: Create
            "Action: Random;"
            "Action: Input;"
            "Action: File",

            // Mode: Update
            "",

            // Mode: Search
            "",
        },

        // action_selection
        std::vector<int>(3),
    };

    using internal::BaseScene::button_size;
    using internal::BaseScene::head_offset;
    using internal::BaseScene::options_head;

    gui::GuiArray<int, max_size> m_array{};
    core::Deque<gui::GuiArray<int, max_size>> m_sequence;

    bool m_go{};
    component::TextInput m_text_input;
    component::TextInput m_index_input;
    component::FileDialog m_file_dialog;
    component::SequenceController m_sequence_controller;

    ArrayScene() = default;

    using internal::BaseScene::render_go_button;
    using internal::BaseScene::render_options;
    void render_inputs() override;

    void interact_random();
    void interact_import(core::Deque<int> nums);
    void interact_file_import();
    void interact_update();
    void interact_search();

public:
    ArrayScene(const ArrayScene&) = delete;
    ArrayScene(ArrayScene&&) = delete;
    ArrayScene& operator=(const ArrayScene&) = delete;
    ArrayScene& operator=(ArrayScene&&) = delete;
    ~ArrayScene() override = default;

    static ArrayScene& get_instance();

    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_ARRAY_SCENE_HPP_
