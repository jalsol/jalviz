#ifndef SCENE_SCENE_OPTIONS_HPP_
#define SCENE_SCENE_OPTIONS_HPP_

#include <cstddef>
#include <vector>

namespace scene::internal {

struct SceneOptions {
    const std::size_t max_size{};
    const char* mode_labels{};
    int mode_selection{};
    std::vector<const char*> action_labels;
    std::vector<int> action_selection;
};

}  // namespace scene::internal

#endif  // SCENE_SCENE_OPTIONS_HPP_
