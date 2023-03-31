#ifndef SCENE_SCENE_REGISTRY_HPP_
#define SCENE_SCENE_REGISTRY_HPP_

#include <array>

#include "array_scene.hpp"
#include "base_linked_list_scene.hpp"
#include "base_scene.hpp"
#include "dynamic_array_scene.hpp"
#include "menu_scene.hpp"
#include "queue_scene.hpp"
#include "stack_scene.hpp"

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
    internal::BaseScene* scene_ptr{};
    SceneRegistry();

    bool m_should_close{};
    int m_current_scene{};

    const std::array<internal::BaseScene* const, 8> m_registry{{
        &MenuScene::get_instance(),
        &ArrayScene::get_instance(),
        &DynamicArrayScene::get_instance(),
        &LinkedListScene::get_instance(),
        &DoublyLinkedListScene::get_instance(),
        &CircularLinkedListScene::get_instance(),
        &StackScene::get_instance(),
        &QueueScene::get_instance(),
    }};

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
