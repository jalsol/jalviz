#ifndef SCENE_SCENE_REGISTRY_HPP_
#define SCENE_SCENE_REGISTRY_HPP_

#include "base_scene.hpp"

namespace scene {

enum SceneId {
    Menu,
    StaticArray,
    DynamicArray,
    SinglyLinkedList,
    DoublyLinkedList,
    CircularLinkedList,
    Stack,
    Queue,
};

class SceneRegistry {
private:
    internal::BaseScene* scene_ptr{nullptr};
    SceneRegistry();

public:
    SceneRegistry(const SceneRegistry&) = delete;
    SceneRegistry(SceneRegistry&&) = delete;
    SceneRegistry& operator=(const SceneRegistry&) = delete;
    SceneRegistry& operator=(SceneRegistry&&) = delete;
    ~SceneRegistry() = default;

    static SceneRegistry& get_instance();

    void set_scene(int scene_type);
    void render();
    void interact();
};

}  // namespace scene

#endif  // SCENE_SCENE_REGISTRY_HPP_
