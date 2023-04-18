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

class SettingsScene : public internal::BaseScene {
private:
    static constexpr Vector2 head_pos{400, 70};
    std::array<component::TextInput, Settings::num_color> m_inputs{};

    int m_selected{};

    component::FileDialog m_open_file;
    component::FileDialog m_save_file{3, "Save file...", "Save file"};
    int m_open{};
    int m_save{};

    void set_buffer();
    void set_color();
    void open_from_file(const std::string& path);

public:
    SettingsScene();

    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_SETTINGS_SCENE_HPP_
