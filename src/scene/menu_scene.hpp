#ifndef SCENE_MENU_SCENE_HPP_
#define SCENE_MENU_SCENE_HPP_

#include <array>

#include "base_scene.hpp"
#include "component/menu_item.hpp"
#include "scene_id.hpp"

namespace scene {

/**
 * @brief The menu scene
 */

class MenuScene : public internal::BaseScene {
public:
    /**
     * @brief Construct a new MenuScene object
     */
    MenuScene();

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
     * @brief Whether a next scene is selected
     */
    bool m_start{};

    /**
     * @brief Whether to quit the program
     */
    bool m_quit{};

    /**
     * @brief The next scene to be rendered
     */
    SceneId m_next_scene{};

    /**
     * @brief The labels for the menu items
     */
    static constexpr std::array<const char*, 7> labels = {{
        "Array",
        "Dynamic Array",
        "Linked List",
        "Doubly Linked List",
        "Circular Linked List",
        "Stack",
        "Queue",
    }};

    /**
     * @brief The image paths for the menu items
     */
    static constexpr std::array<const char*, 7> img_paths = {{
        "data/preview/array.png",
        "data/preview/dynamic_array.png",
        "data/preview/linked_list.png",
        "data/preview/doubly_linked_list.png",
        "data/preview/circular_linked_list.png",
        "data/preview/stack.png",
        "data/preview/queue.png",
    }};

    /**
     * @brief The menu items
     */
    std::array<component::MenuItem, 7> m_menu_items{};
};

}  // namespace scene

#endif  // SCENE_MENU_SCENE_HPP_
