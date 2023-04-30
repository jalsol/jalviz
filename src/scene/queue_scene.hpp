#ifndef SCENE_QUEUE_SCENE_HPP_
#define SCENE_QUEUE_SCENE_HPP_

#include <array>

#include "base_scene.hpp"
#include "component/file_dialog.hpp"
#include "core/doubly_linked_list.hpp"
#include "core/queue.hpp"
#include "gui/queue_gui.hpp"
#include "raygui.h"

namespace scene {

/**
 * @brief The queue scene
 */

class QueueScene : public internal::BaseScene {
public:
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
     * @brief The scene options
     */
    internal::SceneOptions scene_options{
        // max_size
        8,  // NOLINT

        // mode_labels
        "Mode: Create;"
        "Mode: Push;"
        "Mode: Pop;"
        "Mode: Clear",

        // mode_selection
        0,

        // action_labels
        {
            // Mode: Create
            "Action: Random;"
            "Action: Input;"
            "Action: File",

            // Mode: Push
            "",

            // Mode: Pop
            "",

            // Mode: Clear
            "",
        },

        // action_selection
        core::DoublyLinkedList<int>{0, 0, 0, 0},
    };

    using internal::BaseScene::button_size;
    using internal::BaseScene::head_offset;
    using internal::BaseScene::options_head;

    /**
     * @brief The queue
     */
    gui::GuiQueue<int> m_queue{
        gui::GuiNode<int>{1},
        gui::GuiNode<int>{2},
        gui::GuiNode<int>{3},
    };

    /**
     * @brief The sequence of queues to be rendered
     */
    core::DoublyLinkedList<gui::GuiQueue<int>> m_sequence;

    /**
     * @brief Whether the go button is pressed
     */
    bool m_go{};
    using internal::BaseScene::m_code_highlighter;
    using internal::BaseScene::m_file_dialog;
    using internal::BaseScene::m_sequence_controller;
    using internal::BaseScene::m_text_input;

    using internal::BaseScene::render_go_button;
    using internal::BaseScene::render_options;

    /**
     * @brief Renders the inputs
     */
    void render_inputs() override;

    /**
     * @brief Interacts with random mode
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
     * @brief Interacts with push mode
     */
    void interact_push();

    /**
     * @brief Interacts with pop mode
     */
    void interact_pop();

    /**
     * @brief Interacts with clear mode
     */
    void interact_clear();
};

}  // namespace scene

#endif  // SCENE_QUEUE_SCENE_HPP_
