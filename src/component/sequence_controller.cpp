#include "sequence_controller.hpp"

#include <algorithm>

#include "constants.hpp"
#include "raygui.h"
#include "raylib.h"

namespace component {

void SequenceController::set_max_value(int num) { m_num_steps = num; }

void SequenceController::set_progress_value(int value) {
    m_progress_value = value;
}

void SequenceController::set_run_all(bool run_all) { m_run_all = run_all; }

bool SequenceController::get_run_all() const { return m_run_all; }

int SequenceController::get_progress_value() const { return m_progress_value; }

void SequenceController::render() {
    Rectangle replay_shape{button_size.x * 0.5F,
                           constants::scene_height - 1.5F * button_size.x,
                           button_size.x, button_size.y};

    Rectangle prev_shape{
        replay_shape.x + replay_shape.width + button_size.x * 0.5F,
        replay_shape.y, button_size.x, button_size.y};

    Rectangle progress_shape{prev_shape.x + button_size.x * 1.5F,
                             replay_shape.y, 360, button_size.y};

    Rectangle next_shape{
        progress_shape.x + progress_shape.width + button_size.x * 0.5F,
        replay_shape.y, button_size.x, button_size.y};

    m_replay = GuiButton(replay_shape, "R");
    m_prev = GuiButton(prev_shape, "<");
    m_progress_value =
        (int)GuiProgressBar(progress_shape, nullptr, nullptr,
                            (float)m_progress_value, 0, (float)m_num_steps);
    m_next = GuiButton(next_shape, ">");
}

bool SequenceController::interact() {
    if (m_replay) {
        set_progress_value(0);
        set_run_all(true);
        return true;
    }

    if (m_prev) {
        set_progress_value(std::max(get_progress_value() - 1, 0));
        return true;
    }

    if (m_next) {
        set_progress_value(std::min(get_progress_value() + 1, m_num_steps));
        return true;
    }

    return false;
}

}  // namespace component
