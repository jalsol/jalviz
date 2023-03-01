#include "sidebar.hpp"

#include "constants.hpp"
#include "raygui.h"
#include "raylib.h"
#include "scene/scene_registry.hpp"
#include "utils.hpp"

namespace component {

void SideBar::render() {
    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();
    int options_head = 2 * constants::sidebar_width;

    m_next_scene = GuiToggleGroup(
        Rectangle{0, sidebar_width / 1.75, sidebar_width, button_height},
        sidebar_labels, registry.get_scene());
}

void SideBar::interact() {
    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();
    registry.set_scene(m_next_scene);
}

}  // namespace component
