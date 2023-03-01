#include "constants.hpp"
#include "raygui.h"
#include "scene/scene_registry.hpp"

int main() {
    InitWindow(constants::scene_width, constants::scene_height,
               "VisuAlgo.net clone in C++ by @jalsol");
    SetTargetFPS(constants::frames_per_second);

    GuiLoadStyle("data/bluish_open_sans.rgs");

    scene::SceneRegistry& registry = scene::SceneRegistry::get_instance();

    while (!WindowShouldClose()) {
        registry.interact();

        BeginDrawing();
        {
            ClearBackground(WHITE);

            DrawRectangle(0, 0, constants::scene_width,
                          constants::navbar_height, BLUE);

            registry.render();
        }
        EndDrawing();
    }

    return 0;
}
