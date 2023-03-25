#ifndef SCENE_ARRAY_SCENE_HPP_
#define SCENE_ARRAY_SCENE_HPP_

#include <array>
#include <cstddef>

#include "base_scene.hpp"
#include "constants.hpp"
#include "gui/array_gui.hpp"
#include "gui_file_dialog.h"
#include "raygui.h"
#include "raylib.h"

namespace scene {

class ArrayScene : public internal::BaseScene {
private:
    static constexpr std::size_t max_size = 8;
    static constexpr int num_modes = 3;
    static constexpr const char* mode_labels =
        "Mode: Create;"
        "Mode: Update;"
        "Mode: Search";
    static constexpr std::array<const char*, num_modes> action_labels = {
        // Mode: Create
        "Action: Random;"
        "Action: Input;"
        "Action: File",

        // Mode: Update
        "",

        // Mode: Search
        "",
    };
    static constexpr int head_offset = 20;
    static constexpr Vector2 button_size{200, 50};

    gui::GuiArray<int, max_size> m_array{};

    int options_head{};

    int m_mode_selection{};
    std::array<int, num_modes> m_action_selection{};

    bool m_go{};
    char m_text_input[constants::text_buffer_size] = "";  // NOLINT

    GuiFileDialogState m_file_dialog_state{
        InitGuiFileDialog(GetWorkingDirectory())};
    char m_file_input[constants::text_buffer_size] = "";  // NOLINT

    char m_index_input[constants::text_buffer_size] = "";  // NOLINT

    ArrayScene() = default;

    void render_options();
    void render_inputs();
    [[nodiscard]] bool render_go_button() const;
    void render_text_input();
    void render_file_input();
    void render_index_input();

    void interact_random();
    void interact_import();
    void interact_file_import();
    void interact_update();

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
