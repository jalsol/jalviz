#include <iostream>

#include "component/sidebar.hpp"
#include "constants.hpp"
#include "raygui.h"
#include "scene/scene_registry.hpp"
#include "settings.hpp"

int main() {
    InitWindow(constants::scene_width, constants::scene_height,
               "VisuAlgo.net clone in C++ by @jalsol");
    SetTargetFPS(constants::frames_per_second);

    GuiLoadStyle("data/bluish_open_sans.rgs");

    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();
    component::SideBar sidebar;

    bool should_close = false;

    do {
        // NOTE: The order is important
        sidebar.interact();
        registry.interact();

        BeginDrawing();
        {
            ClearBackground(
                Settings::get_instance().get_color(Settings::num_color - 1));

            // NOTE: The order is important
            registry.render();
            sidebar.render();
        }
        EndDrawing();

        should_close = registry.should_close() || WindowShouldClose();
    } while (!should_close);

    CloseWindow();

    return 0;
}
