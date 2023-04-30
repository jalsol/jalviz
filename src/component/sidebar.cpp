#include "sidebar.hpp"

#include "constants.hpp"
#include "raygui.h"
#include "raylib.h"
#include "scene/scene_id.hpp"
#include "scene/scene_registry.hpp"
#include "utils.hpp"

namespace component {

void SideBar::render() {
    (m_edit_mode) ? GuiLock() : GuiUnlock();

    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();
    int options_head = 2 * constants::sidebar_width;

    constexpr float scale = 0.2;

    constexpr Rectangle menu_button_shape{20, 20, button_height * 2,
                                          button_height};
    constexpr Rectangle selection_shape{
        menu_button_shape.x + menu_button_shape.width + 10, menu_button_shape.y,
        button_width, button_height};
    constexpr Rectangle settings_button_shape{
        constants::scene_width - button_height - 20, 20, button_height,
        button_height};

    m_next_scene = registry.get_scene();

    bool menu_is_next = m_next_scene == scene::Menu;
    bool settings_is_next = m_next_scene == scene::Settings;

    if (!menu_is_next) {
        m_return_menu = GuiButton(menu_button_shape, "#118#Menu");
    }

    int next_scene = m_next_scene;

    if (!menu_is_next && !settings_is_next) {
        if (GuiDropdownBox(selection_shape, sidebar_labels, &next_scene,
                           m_edit_mode)) {
            m_pressed = true;
            m_edit_mode ^= 1;
        }
    }

    m_next_scene = scene::SceneId(next_scene);

    m_return_settings = GuiButton(settings_button_shape, "#142#");
}

void SideBar::interact() {
    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();
    bool menu_is_current = registry.get_scene() == scene::Menu;
    bool settings_is_current = registry.get_scene() == scene::Settings;

    if (!menu_is_current) {
        if (m_return_menu) {
            registry.set_scene(scene::Menu);
            m_return_menu = false;
            return;
        }
    }

    if (!menu_is_current && !settings_is_current) {
        if (m_pressed) {
            registry.set_scene(m_next_scene);
            m_pressed = false;
            return;
        }
    }

    if (m_return_settings) {
        if (settings_is_current) {
            registry.set_scene(scene::SceneId(m_scene_before_settings));
        } else {
            m_scene_before_settings = registry.get_scene();
            registry.set_scene(scene::Settings);
        }
        m_return_settings = false;
        return;
    }
}

}  // namespace component
