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

    // component::MenuItem array_item;
    // component::MenuItem dyn_array_item;
    // component::MenuItem linked_list_item;
    // component::MenuItem doubly_linked_list_item;
    // component::MenuItem circular_linked_list_item;
    // component::MenuItem stack_item;
    // component::MenuItem queue_item;

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

    MenuScene();

public:
    MenuScene(const MenuScene&) = delete;
    MenuScene(MenuScene&&) = delete;
    MenuScene& operator=(const MenuScene&) = delete;
    MenuScene& operator=(MenuScene&&) = delete;
    ~MenuScene() override = default;

    static MenuScene& get_instance();

    void render() override;
    void interact() override;
};

}  // namespace scene

#endif  // SCENE_MENU_SCENE_HPP_
