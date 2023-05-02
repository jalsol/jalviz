#ifndef SCENE_SETTINGS_SCENE_HPP_
#define SCENE_SETTINGS_SCENE_HPP_

#include <array>
#include <constants.hpp>
#include <string>

#include "base_scene.hpp"
#include "component/file_dialog.hpp"
#include "component/text_input.hpp"
#include "raylib.h"
#include "settings.hpp"

namespace scene {

/**
 * @brief The settings scene
 */

class SettingsScene : public internal::BaseScene {
public:
    /**
     * @brief Construct a new SettingsScene object
     */
    SettingsScene();

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
     * @brief The position of the head input
     */
    static constexpr Vector2 head_pos{400, 70};

    /**
     * @brief The array of text inputs for colors
     */
    std::array<component::TextInput, Settings::num_color> m_inputs{};

    /**
     * @brief The selected color for editing
     */
    int m_selected{};

    /**
     * @brief The open file dialog
     */
    component::FileDialog m_open_file;

    /**
     * @brief The save file dialog
     */
    component::FileDialog m_save_file{3, "Save file...", "Save file"};

    /**
     * @brief The state of the open file dialog
     */
    int m_open{-1};

    /**
     * @brief The state of the save file dialog
     */
    int m_save{-1};

    /**
     * @brief Sets the buffer for the text inputs
     */
    void set_buffer();

    /**
     * @brief Sets the color for the text inputs
     */
    void set_color();

    /**
     * @brief Loads the settings from the file
     */
    void open_from_file(const std::string& path);
};

}  // namespace scene

#endif  // SCENE_SETTINGS_SCENE_HPP_
