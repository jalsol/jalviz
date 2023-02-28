#ifndef SCENE_STACK_SCENE_HPP_
#define SCENE_STACK_SCENE_HPP_

#include <array>

#include "base_scene.hpp"
#include "core/stack.hpp"
#include "gui/stack.hpp"

namespace scene {

class StackScene : public BaseScene<gui::Stack<int>> {
private:
    static constexpr std::size_t max_size = 8;

    gui::Stack<int> m_stack{
        gui::Node<int>{1},
        gui::Node<int>{2},
        gui::Node<int>{3},
    };

    static constexpr int num_modes = 4;

    static constexpr const char* mode_labels =
        "Mode: Create;Mode: Push;Mode: Pop;Mode: Peek";

    static constexpr std::array<const char*, num_modes> action_labels = {
        "Action: Random;Action: Input;Action: File",
        "",
        "",
        "",
    };

    static constexpr int head_offset = 20;
    static constexpr Vector2 button_size{200, 50};

    int options_head{};

    int m_mode_selection{};
    std::array<int, num_modes> m_action_selection{};

    bool m_go{};
    char m_text_input[constants::text_buffer_size] = "";  // NOLINT

    void render_options();
    void render_inputs();
    [[nodiscard]] bool render_go_button() const;
    void render_text_input();

    void interact_random();

public:
    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_STACK_SCENE_HPP_