#include "base_scene.hpp"

#include <cstring>

#include "constants.hpp"
#include "raygui.h"

namespace scene::internal {

bool BaseScene::render_go_button() const {
    Rectangle shape{options_head, constants::scene_height - button_size.y,
                    button_size.y, button_size.y};
    return GuiButton(shape, "Go");
}

void BaseScene::render_options(SceneOptions& scene_config) {
    (m_edit_mode || m_edit_action) ? GuiLock() : GuiUnlock();

    options_head = 2 * constants::sidebar_width;

    Rectangle mode_button_shape{options_head,
                                constants::scene_height - button_size.y,
                                button_size.x, button_size.y};

    options_head += (button_size.x + head_offset);

    int& mode = scene_config.mode_selection;

    if (GuiDropupBox(mode_button_shape, scene_config.mode_labels, &mode,
                     m_edit_mode)) {
        m_edit_mode ^= 1;
    }

    if (std::strlen(scene_config.action_labels.at(mode)) != 0) {
        Rectangle action_button_shape{options_head,
                                      constants::scene_height - button_size.y,
                                      button_size.x, button_size.y};

        options_head += (button_size.x + head_offset);

        int& action_selection = scene_config.action_selection.at(mode);

        if (GuiDropupBox(action_button_shape,
                         scene_config.action_labels.at(mode), &action_selection,
                         m_edit_action)) {
            m_edit_action ^= 1;
        }

        // scene_config.action_selection.at(mode) = GuiComboBox(
        //     action_button_shape, scene_config.action_labels.at(mode),
        //     scene_config.action_selection.at(mode));
    }

    render_inputs();
}

}  // namespace scene::internal
