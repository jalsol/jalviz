#ifndef SCENE_SCENE_REGISTRY_HPP_
#define SCENE_SCENE_REGISTRY_HPP_

#include "base_scene.hpp"

namespace scene {

enum SceneId {
    Menu,
    Array,
    DynamicArray,
    LinkedList,
    DoublyLinkedList,
    CircularLinkedList,
    Stack,
    Queue,
};

class SceneRegistry {
private:
    internal::BaseScene* scene_ptr{nullptr};
    SceneRegistry();

    bool m_should_close{};
    int m_current_scene{};

public:
    SceneRegistry(const SceneRegistry&) = delete;
    SceneRegistry(SceneRegistry&&) = delete;
    SceneRegistry& operator=(const SceneRegistry&) = delete;
    SceneRegistry& operator=(SceneRegistry&&) = delete;
    ~SceneRegistry() = default;

    static SceneRegistry& get_instance();

    void set_scene(int scene_type);
    int get_scene() const;
    void render();
    void interact();
    bool should_close() const;
    void close_window();
};

}  // namespace scene

#endif  // SCENE_SCENE_REGISTRY_HPP_
