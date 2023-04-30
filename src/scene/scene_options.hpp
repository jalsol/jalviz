#ifndef SCENE_SCENE_OPTIONS_HPP_
#define SCENE_SCENE_OPTIONS_HPP_

#include <cstddef>

#include "core/doubly_linked_list.hpp"

namespace scene::internal {

/**
 * @brief The scene options
 */

struct SceneOptions {
    /**
     * @brief The maximum size of the container
     */
    const std::size_t max_size{};

    /**
     * @brief The mode labels
     */
    const char* mode_labels{};

    /**
     * @brief The currently selected mode
     */
    int mode_selection{};

    /**
     * @brief The action labels
     */
    core::DoublyLinkedList<const char*> action_labels;

    /**
     * @brief The currently selected actions for each mode
     */
    core::DoublyLinkedList<int> action_selection;
};

}  // namespace scene::internal

#endif  // SCENE_SCENE_OPTIONS_HPP_
