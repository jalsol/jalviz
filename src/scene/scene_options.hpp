#ifndef SCENE_SCENE_OPTIONS_HPP_
#define SCENE_SCENE_OPTIONS_HPP_

#include <cstddef>

#include "core/doubly_linked_list.hpp"

namespace scene::internal {

struct SceneOptions {
    const std::size_t max_size{};
    const char* mode_labels{};
    int mode_selection{};
    core::DoublyLinkedList<const char*> action_labels;
    core::DoublyLinkedList<int> action_selection;
};

}  // namespace scene::internal

#endif  // SCENE_SCENE_OPTIONS_HPP_
