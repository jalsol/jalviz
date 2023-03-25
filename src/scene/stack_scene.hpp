#ifndef SCENE_STACK_SCENE_HPP_
#define SCENE_STACK_SCENE_HPP_

#include <array>

#include "base_scene.hpp"
#include "component/file_dialog.hpp"
#include "component/text_input.hpp"
#include "core/stack.hpp"
#include "gui/stack_gui.hpp"
#include "raygui.h"

namespace scene {

class StackScene : public internal::BaseScene {
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

    gui::GuiStack<int> m_stack{
        gui::GuiNode<int>{1},
        gui::GuiNode<int>{2},
        gui::GuiNode<int>{3},
    };

    float options_head{};

    int m_mode_selection{};
    std::array<int, num_modes> m_action_selection{};

    bool m_go{};
    component::TextInput m_text_input;
    component::FileDialog m_file_dialog;

    StackScene() = default;

    void render_options();
    void render_inputs();
    [[nodiscard]] bool render_go_button() const;

    void interact_random();
    void interact_import(core::Deque<int> nums, bool clear, int amount_to_take);
    void interact_file_import();

public:
    StackScene(const StackScene&) = delete;
    StackScene(StackScene&&) = delete;
    StackScene& operator=(const StackScene&) = delete;
    StackScene& operator=(StackScene&&) = delete;
    ~StackScene() override = default;

    static StackScene& get_instance();

    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_STACK_SCENE_HPP_
