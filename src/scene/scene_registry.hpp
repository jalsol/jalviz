#ifndef SCENE_SCENE_REGISTRY_HPP_
#define SCENE_SCENE_REGISTRY_HPP_

#include <array>
#include <memory>

#include "array_scene.hpp"
#include "base_linked_list_scene.hpp"
#include "base_scene.hpp"
#include "dynamic_array_scene.hpp"
#include "menu_scene.hpp"
#include "queue_scene.hpp"
#include "scene_id.hpp"
#include "settings_scene.hpp"
#include "stack_scene.hpp"

namespace scene {

/**
 * @brief The scene registry
 */
class SceneRegistry {
public:
    /**
     * @brief Deleted copy constructor
     */
    SceneRegistry(const SceneRegistry&) = delete;

    /**
     * @brief Deleted move constructor
     */
    SceneRegistry(SceneRegistry&&) = delete;

    /**
     * @brief Deleted copy assignment operator
     */
    SceneRegistry& operator=(const SceneRegistry&) = delete;

    /**
     * @brief Deleted move assignment operator
     */
    SceneRegistry& operator=(SceneRegistry&&) = delete;

    /**
     * @brief Destroy the Scene Registry object
     */
    ~SceneRegistry() = default;

    /**
     * @brief Get the instance object
     * @return SceneRegistry& The instance
     */
    static SceneRegistry& get_instance();

    /**
     * @brief Sets the scene
     * @param scene_type The scene type
     */
    void set_scene(SceneId scene_type);

    /**
     * @brief Gets the scene
     * @return SceneId The scene
     */
    SceneId get_scene() const;

    /**
     * @brief Renders the scene
     */
    void render();

    /**
     * @brief Interacts with the scene
     */
    void interact();

    /**
     * @brief Checks if the window should close
     * @retval true If the window should close
     * @retval false If the window should not close
     */
    bool should_close() const;

    /**
     * @brief Closes the window
     */
    void close_window();

private:
    /**
     * @brief The pointer to the current scene
     */
    internal::BaseScene* scene_ptr{};

    /**
     * @brief Construct a new Scene Registry object
     */
    SceneRegistry();

    /**
     * @brief Whether the window should close
     */
    bool m_should_close{};

    /**
     * @brief The id of the current scene
     */
    SceneId m_current_scene{};

    /**
     * @brief The registry of scenes
     */
    const std::array<const std::unique_ptr<internal::BaseScene>, 9> m_registry{{
        std::make_unique<ArrayScene>(),
        std::make_unique<DynamicArrayScene>(),
        std::make_unique<LinkedListScene>(),
        std::make_unique<DoublyLinkedListScene>(),
        std::make_unique<CircularLinkedListScene>(),
        std::make_unique<StackScene>(),
        std::make_unique<QueueScene>(),
        std::make_unique<MenuScene>(),
        std::make_unique<SettingsScene>(),
    }};
};

}  // namespace scene

#endif  // SCENE_SCENE_REGISTRY_HPP_
