#include "scene_registry.hpp"
#include "menu_scene.hpp"
#include "stack_scene.hpp"
#include "queue_scene.hpp"

namespace scene {

SceneRegistry::SceneRegistry() {
    set_scene(Menu);
}

SceneRegistry& SceneRegistry::get_instance() {
    static SceneRegistry registry;
    return registry;
}

void SceneRegistry::set_scene(int scene_type) {
    switch (scene_type) {
        case Menu: {
            scene_ptr = &MenuScene::get_instance();
        } break;

        case Stack: {
            scene_ptr = &StackScene::get_instance();
        } break;

        case Queue: {
            scene_ptr = &QueueScene::get_instance();
        } break;

        default:
            __builtin_unreachable();
    }
}

void SceneRegistry::render() {
    scene_ptr->render();
}

void SceneRegistry::interact() {
    scene_ptr->interact();
}

} // namespace scene
