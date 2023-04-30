#include "scene_registry.hpp"

namespace scene {

SceneRegistry::SceneRegistry() { set_scene(Menu); }

SceneRegistry& SceneRegistry::get_instance() {
    static SceneRegistry registry;
    return registry;
}

void SceneRegistry::set_scene(SceneId scene_type) {
    m_current_scene = scene_type;
    scene_ptr = m_registry.at(scene_type).get();
}

SceneId SceneRegistry::get_scene() const { return m_current_scene; }

void SceneRegistry::render() { scene_ptr->render(); }

void SceneRegistry::interact() { scene_ptr->interact(); }

bool SceneRegistry::should_close() const { return m_should_close; }

void SceneRegistry::close_window() { m_should_close = true; }

}  // namespace scene
