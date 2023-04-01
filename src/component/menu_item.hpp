#ifndef COMPONENT_MENU_ITEM_HPP_
#define COMPONENT_MENU_ITEM_HPP_

#include "raylib.h"

namespace component {

class MenuItem {
private:
    int m_scene{};
    int m_x{};
    int m_y{};
    Texture2D m_texture{};
    const char* m_text{};

    bool m_clicked{};

public:
    static constexpr int block_width = 300;
    static constexpr int block_height = 200;
    static constexpr int button_width = block_width;
    static constexpr int button_height = 50;

    MenuItem() = default;
    MenuItem(int scene, const char* text, int x, int y, const char* img_path);

    int x() const;
    int y() const;

    void render();
    bool clicked() const;
    void reset();
};

}  // namespace component

#endif  // COMPONENT_MENU_ITEM_HPP_
