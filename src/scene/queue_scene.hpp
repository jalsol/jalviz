#ifndef SCENE_QUEUE_SCENE_HPP_
#define SCENE_QUEUE_SCENE_HPP_

#include <array>

#include "base_scene.hpp"
#include "core/queue.hpp"
#include "gui/queue_gui.hpp"
#include "gui_file_dialog.h"
#include "raygui.h"

namespace scene {

class QueueScene : public internal::BaseScene {
private:
    static constexpr std::size_t max_size = 8;
    static constexpr int num_modes = 3;
    static constexpr const char* mode_labels =
        "Mode: Create;"
        "Mode: Push;"
        "Mode: Pop";
    static constexpr std::array<const char*, num_modes> action_labels = {
        // Mode: Create
        "Action: Random;"
        "Action: Input;"
        "Action: File",

        // Mode: Push
        "",

        // Mode: Pop
        "",
    };
    static constexpr int head_offset = 20;
    static constexpr Vector2 button_size{200, 50};

    gui::Queue<int> m_queue{
        gui::Node<int>{1},
        gui::Node<int>{2},
        gui::Node<int>{3},
    };

    int options_head{};

    int m_mode_selection{};
    std::array<int, num_modes> m_action_selection{};

    bool m_go{};
    char m_text_input[constants::text_buffer_size] = "";  // NOLINT

    GuiFileDialogState m_file_dialog_state{
        InitGuiFileDialog(GetWorkingDirectory())};
    char m_file_input[constants::text_buffer_size] = "";  // NOLINT

    QueueScene() = default;

    void render_options();
    void render_inputs();
    [[nodiscard]] bool render_go_button() const;
    void render_text_input();
    void render_file_input();

    void interact_random();
    void interact_import(bool clear, int amount_to_take);
    void interact_file_import();

public:
    QueueScene(const QueueScene&) = delete;
    QueueScene(QueueScene&&) = delete;
    QueueScene& operator=(const QueueScene&) = delete;
    QueueScene& operator=(QueueScene&&) = delete;
    ~QueueScene() override = default;

    static QueueScene& get_instance();

    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_QUEUE_SCENE_HPP_
