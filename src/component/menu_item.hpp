#ifndef COMPONENT_MENU_ITEM_HPP_
#define COMPONENT_MENU_ITEM_HPP_

#include "raylib.h"

namespace component {

/**
 * @brief Items in the menu screen to navigate to other screens
 */

class MenuItem {
public:
    /**
     * @brief The width of the menu item frame
     */
    static constexpr int block_width = 300;

    /**
     * @brief The height of the menu item frame
     */
    static constexpr int block_height = 200;

    /**
     * @brief The width of the button on the menu item
     */
    static constexpr int button_width = block_width;

    /**
     * @brief The height of the button on the menu item
     */
    static constexpr int button_height = 50;

    /**
     * @brief Constructs a MenuItem object
     */
    MenuItem() = default;

    /**
     * @brief Constructs a MenuItem object
     * @param text the text of the menu item
     * @param x the x position of the menu item
     * @param y the y position of the menu item
     * @param img_path the path to the image of the menu item
     */
    MenuItem(const char* text, int x, int y, const char* img_path);

    /**
     * @brief Returns the x position of the menu item
     * @return the x position of the menu item
     */
    int x() const;

    /**
     * @brief Returns the y position of the menu item
     * @return the y position of the menu item
     */
    int y() const;

    /**
     * @brief Renders the menu item
     */
    void render();

    /**
     * @brief Checks if the menu item was clicked
     * @retval true The menu item was clicked
     * @retval false The menu item was not clicked
     */
    bool clicked() const;

    /**
     * @brief Resets the menu item
     */
    void reset();

private:
    /**
     * @brief The x position of the menu item
     */
    int m_x{};

    /**
     * @brief The y position of the menu item
     */
    int m_y{};

    /**
     * @brief The texture of the menu item
     */
    Texture2D m_texture{};

    /**
     * @brief The text of the menu item
     */
    const char* m_text{};

    /**
     * @brief Whether the menu item was clicked
     */
    bool m_clicked{};
};

}  // namespace component

#endif  // COMPONENT_MENU_ITEM_HPP_
