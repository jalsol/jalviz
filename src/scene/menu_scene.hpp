#ifndef SCENE_MENU_SCENE_HPP_
#define SCENE_MENU_SCENE_HPP_

#include <array>

#include "base_scene.hpp"
#include "component/menu_item.hpp"

namespace scene {

class MenuScene : public internal::BaseScene {
private:
    bool m_start{};
    bool m_quit{};
    int m_next_scene{};

    static constexpr std::array<const char*, 7> labels = {{
        "Array",
        "Dynamic Array",
        "Linked List",
        "Doubly Linked List",
        "Circular Linked List",
        "Stack",
        "Queue",
    }};

    static constexpr std::array<const char*, 7> img_paths = {{
        "data/preview/array.png",
        "data/preview/dynamic_array.png",
        "data/preview/linked_list.png",
        "data/preview/doubly_linked_list.png",
        "data/preview/circular_linked_list.png",
        "data/preview/stack.png",
        "data/preview/queue.png",
    }};

    std::array<component::MenuItem, 7> m_menu_items{};

public:
    MenuScene();
    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_MENU_SCENE_HPP_
