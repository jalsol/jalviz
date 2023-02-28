#include "constants.hpp"
#include "raygui.h"
#include "scene/menu_scene.hpp"
#include "scene/stack_scene.hpp"

int main() {
    InitWindow(constants::scene_width, constants::scene_height,
               "VisuAlgo.net clone in C++ by @jalsol");
    SetTargetFPS(constants::frames_per_second);

    GuiLoadStyle("./data/bluish_open_sans.rgs");

    scene::StackScene scene;

    while (!WindowShouldClose()) {
        scene.interact();

        BeginDrawing();
        {
            ClearBackground(WHITE);
            scene.render();
        }
        EndDrawing();
    }

    return 0;
}
