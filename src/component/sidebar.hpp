#ifndef COMPONENT_SIDEBAR_HPP_
#define COMPONENT_SIDEBAR_HPP_

#include <array>

#include "constants.hpp"
#include "scene/scene_registry.hpp"

namespace component {

/**
 * @brief "Side bar" for extra navigation
 * @note Should have been renamed to navbar instead
 */

class SideBar {
public:
    /**
     * @brief Constructs a SideBar object
     */
    void render();

    /**
     * @brief Interacts with the SideBar object
     */
    void interact();

private:
    /**
     * @brief The number of scenes
     */
    static constexpr int num_scenes = 8;

    /**
     * @brief The width of the side bar
     */
    static constexpr int button_width = constants::sidebar_width;

    /**
     * @brief The height of the side bar
     */
    static constexpr int button_height = 50;

    /**
     * @brief The labels of each button of the side bar
     */
    static constexpr const char* sidebar_labels =
        "Array;"
        "Dynamic Array;"
        "Linked List;"
        "Doubly Linked List;"
        "Circular Linked List;"
        "Stack;"
        "Queue";

    /**
     * @brief The index of the scene to be navigated to
     */
    int m_next_scene{};

    /**
     * @brief Whether the edit mode is on
     */
    bool m_edit_mode{};

    /**
     * @brief Whether to return to the menu
     */
    bool m_return_menu{};

    /**
     * @brief Whether to return to the settings
     */
    bool m_return_settings{};

    /**
     * @brief The scene before the settings is clicked
     */
    int m_scene_before_settings{};

    /**
     * @brief Whether the dropdown box is pressed
     */
    bool m_pressed{};
};

}  // namespace component

#endif  // COMPONENT_SIDEBAR_HPP_
