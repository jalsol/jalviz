#ifndef SCENE_ARRAY_SCENE_HPP_
#define SCENE_ARRAY_SCENE_HPP_

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

/**
 * @brief The array scene
 */

class ArrayScene : public internal::BaseScene {
public:
    /**
     * @brief Construct a new ArrayScene object
     */
    ArrayScene();

    /**
     * @brief Renders the scene
     */
    void render() override;

    /**
     * @brief Interacts with the scene
     */
    void interact() override;

private:
    /**
     * @brief The maximum size of the array
     */
    static constexpr std::size_t max_size = 8;

    /**
     * @brief The scene options
     */
    internal::SceneOptions scene_options{
        // max_size
        max_size,

        // mode_labels
        "Mode: Create;"
        "Mode: Access;"
        "Mode: Update;"
        "Mode: Search;"
        "Mode: Insert;"
        "Mode: Delete",

        // mode_selection
        0,

        // action_labels
        {
            // Mode: Create
            "Action: CreateRandom;Action: Input;Action: File",

            // Mode: Access
            "",

            // Mode: Update
            "",

            // Mode: Search
            "",

            // Mode: Insert
            "",

            // Mode: Delete
            "",
        },

        // action_selection
        core::DoublyLinkedList<int>{0, 0, 0, 0, 0},
    };

    /**
     * @brief The mode ids
     */
    enum ModeId {
        Create,
        Access,
        Update,
        Search,
        Insert,
        Delete,
    };

    /**
     * @brief The "Create" action ids
     */
    enum CreateActionId {
        CreateRandom,
        CreateInput,
        CreateFile,
    };

    using internal::BaseScene::button_size;
    using internal::BaseScene::head_offset;
    using internal::BaseScene::options_head;

    /**
     * @brief The array
     */
    gui::GuiDynamicArray<int> m_array{};

    /**
     * @brief The sequence of arrays to render
     */
    core::DoublyLinkedList<gui::GuiDynamicArray<int>> m_sequence;

    /**
     * @brief Whether the go button was pressed
     */
    bool m_go{};

    using internal::BaseScene::m_file_dialog;
    using internal::BaseScene::m_index_input;
    using internal::BaseScene::m_sequence_controller;
    using internal::BaseScene::m_text_input;

    using internal::BaseScene::render_go_button;
    using internal::BaseScene::render_options;

    /**
     * @brief Renders the inputs
     */
    void render_inputs() override;

    /**
     * @brief Interacts with Createrandom mode
     */
    void interact_random();

    /**
     * @brief Interacts with import mode
     */
    void interact_import(core::Deque<int> nums);

    /**
     * @brief Interacts with file import mode
     */
    void interact_file_import();

    /**
     * @brief Interacts with update mode
     */
    void interact_update();

    /**
     * @brief Interacts with search mode
     */
    void interact_search();

    /**
     * @brief Interacts with insert mode
     */
    void interact_insert();

    /**
     * @brief Interacts with delete mode
     */
    void interact_delete();

    /**
     * @brief Interacts with access mode
     */
    void interact_access();
};

}  // namespace scene

#endif  // SCENE_ARRAY_SCENE_HPP_
