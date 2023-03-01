#include "scene_registry.hpp"

#include "menu_scene.hpp"
#include "queue_scene.hpp"
#include "stack_scene.hpp"

namespace scene {

SceneRegistry::SceneRegistry() { set_scene(Menu); }

SceneRegistry& SceneRegistry::get_instance() {
    static SceneRegistry registry;
    return registry;
}

void SceneRegistry::set_scene(int scene_type) {
    m_current_scene = scene_type;

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

int SceneRegistry::get_scene() const { return m_current_scene; }

void SceneRegistry::render() { scene_ptr->render(); }

void SceneRegistry::interact() { scene_ptr->interact(); }

bool SceneRegistry::should_close() const { return m_should_close; }

void SceneRegistry::close_window() { m_should_close = true; }

}  // namespace scene
