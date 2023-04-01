#include "sidebar.hpp"

#include "constants.hpp"
#include "raygui.h"
#include "raylib.h"
#include "scene/scene_registry.hpp"
#include "utils.hpp"

namespace component {

void SideBar::render() {
    (m_edit_mode) ? GuiLock() : GuiUnlock();

    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();
    int options_head = 2 * constants::sidebar_width;

    constexpr float scale = 0.2;

    Rectangle menu_button_shape{0, 0, button_height * 2, button_height};
    Rectangle selection_shape{
        menu_button_shape.x + menu_button_shape.width + 10, menu_button_shape.y,
        button_width, button_height};

    m_return_menu = GuiButton(menu_button_shape, "#118#Menu");
    m_next_scene = registry.get_scene();

    if (GuiDropdownBox(selection_shape, sidebar_labels, &m_next_scene,
                       m_edit_mode)) {
        m_pressed = true;
        m_edit_mode ^= 1;
    }

    // m_next_scene = GuiToggleGroup(
    //     sidebar_labels, registry.get_scene());
}

void SideBar::interact() {
    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();

    if (m_return_menu) {
        registry.set_scene(scene::Menu);
        return;
    }

    if (m_pressed) {
        registry.set_scene(m_next_scene);
        m_pressed = false;
    }
}

}  // namespace component
