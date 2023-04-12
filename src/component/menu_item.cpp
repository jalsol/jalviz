#include "menu_item.hpp"

#include "raygui.h"
#include "raylib.h"

namespace component {

MenuItem::MenuItem(int scene, const char* text, int x, int y,
                   const char* img_path)
    : m_scene{scene},
      m_text{text},
      m_x{x},
      m_y{y},
      m_texture{LoadTextureFromImage(LoadImage(img_path))} {}

int MenuItem::x() const { return m_x; }
int MenuItem::y() const { return m_y; }

void MenuItem::render() {
    auto mouse = GetMousePosition();
    const Rectangle bound{(float)m_x, (float)m_y, block_width, block_height};
    const Rectangle text_bound{(float)m_x + 20,
                               (float)m_y + block_height - button_height,
                               button_width - 20, button_height};

    DrawRectangleRec(bound, RAYWHITE);
    DrawTexture(m_texture, m_x, m_y, WHITE);
    GuiLabelButton(text_bound, m_text);
    DrawRectangleLinesEx(bound, 2, BLACK);

    if (CheckCollisionPointRec(mouse, bound)) {
        DrawRectangle(m_x, m_y, block_width, block_height,
                      ColorAlpha(BLUE, 0.3));
        m_clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
}

bool MenuItem::clicked() const { return m_clicked; }

void MenuItem::reset() { m_clicked = false; }

}  // namespace component
