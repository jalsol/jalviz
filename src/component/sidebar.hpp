#ifndef COMPONENT_SIDEBAR_HPP_
#define COMPONENT_SIDEBAR_HPP_

#include <array>

#include "constants.hpp"
#include "scene/scene_registry.hpp"

namespace component {

class SideBar {
private:
    static constexpr int num_scenes = 8;

    static constexpr int button_width = constants::sidebar_width;
    static constexpr int button_height = 50;

    static constexpr const char* sidebar_labels =
        "Array;"
        "Dynamic Array;"
        "Linked List;"
        "Doubly Linked List;"
        "Circular Linked List;"
        "Stack;"
        "Queue";

    int m_next_scene{};
    bool m_edit_mode{};
    bool m_return_menu{};
    bool m_pressed{};

public:
    void render();
    void interact();
};

}  // namespace component

#endif  // COMPONENT_SIDEBAR_HPP_
