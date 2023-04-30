#ifndef SCENE_BASE_SCENE_HPP_
#define SCENE_BASE_SCENE_HPP_

#include "component/code_highlighter.hpp"
#include "component/file_dialog.hpp"
#include "component/random_text_input.hpp"
#include "component/sequence_controller.hpp"
#include "raylib.h"
#include "scene_options.hpp"

namespace scene::internal {

/**
 * @brief The base scene class
 */

class BaseScene {
public:
    /**
     * @brief Construct a new BaseScene object
     */
    BaseScene() = default;

    /**
     * @brief Copy constructor (deleted)
     */
    BaseScene(const BaseScene&) = delete;

    /**
     * @brief Move constructor (deleted)
     */
    BaseScene(BaseScene&&) = delete;

    /**
     * @brief Copy assignment (deleted)
     */
    BaseScene& operator=(const BaseScene&) = delete;

    /**
     * @brief Move assignment (deleted)
     */
    BaseScene& operator=(BaseScene&&) = delete;

    /**
     * @brief Destroy the BaseScene object
     */
    virtual ~BaseScene() = default;

    /**
     * @brief Renders the scene
     */
    virtual void render() {}

    /**
     * @brief Interacts with the scene
     */
    virtual void interact() {}

protected:
    /**
     * @brief The size of the buttons
     */
    static constexpr Vector2 button_size{200, 50};

    /**
     * @brief The offset of the widgets
     */
    static constexpr int head_offset = 20;

    /**
     * @brief The head of the options
     */
    float options_head{};

    /**
     * @brief Renders the go button
     * @retval true The go button was pressed
     * @return false The go button was not pressed
     */
    virtual bool render_go_button() const;

    /**
     * @brief Renders the options
     * @param scene_config The scene options
     */
    virtual void render_options(SceneOptions& scene_config);

    /**
     * @brief Renders the inputs
     */
    virtual void render_inputs() {}

    /**
     * @brief The text input for the value
     */
    component::RandomTextInput m_text_input{"value"};

    /**
     * @brief The text input for the index
     */
    component::RandomTextInput m_index_input{"index"};

    /**
     * @brief The file dialog
     */
    component::FileDialog m_file_dialog;

    /**
     * @brief The sequence controller
     */
    component::SequenceController m_sequence_controller;

    /**
     * @brief The code highlighter
     */
    component::CodeHighlighter m_code_highlighter;

    /**
     * @brief Whether the edit mode is enabled
     */
    bool m_edit_mode{};

    /**
     * @brief Whether the edit action is enabled
     */
    bool m_edit_action{};
};

}  // namespace scene::internal

#endif  // SCENE_BASE_SCENE_HPP_
