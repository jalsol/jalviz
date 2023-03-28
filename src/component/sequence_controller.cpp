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

float SequenceController::get_speed_scale() const {
    return (float)m_speed / speed_scale;
}

void SequenceController::reset_anim_counter() { m_anim_counter = 0; }

void SequenceController::inc_anim_counter() { ++m_anim_counter; }

int SequenceController::get_anim_counter() const { return m_anim_counter; }

void SequenceController::set_rerun() {
    reset_anim_counter();
    set_run_all(true);
}

void SequenceController::render() {
    Rectangle replay_shape{button_size.x * 0.5F,
                           constants::scene_height - 1.5F * button_size.x,
                           button_size.x, button_size.y};

    Rectangle prev_frame_shape{
        replay_shape.x + replay_shape.width + button_size.x * 0.5F,
        replay_shape.y, button_size.x, button_size.y};

    Rectangle progress_shape{prev_frame_shape.x + button_size.x * 1.5F,
                             replay_shape.y, 360, button_size.y};

    Rectangle next_frame_shape{
        progress_shape.x + progress_shape.width + button_size.x * 0.5F,
        replay_shape.y, button_size.x, button_size.y};

    Rectangle prev_speed_shape{prev_frame_shape.x + 240,
                               prev_frame_shape.y - 1.5F * button_size.y,
                               button_size.x, button_size.y};

    Rectangle next_speed_shape{next_frame_shape.x,
                               next_frame_shape.y - 1.5F * button_size.y,
                               button_size.x, button_size.y};

    Rectangle speed_shape{prev_speed_shape.x + 1.5F * button_size.x,
                          prev_speed_shape.y, 120, button_size.y};

    m_prev_speed = GuiButton(prev_speed_shape, "<");
    m_next_speed = GuiButton(next_speed_shape, ">");
    GuiStatusBar(speed_shape, TextFormat("Speed: %.2fx", get_speed_scale()));

    m_replay = GuiButton(replay_shape, "R");
    m_prev_frame = GuiButton(prev_frame_shape, "<");
    m_progress_value =
        (int)GuiProgressBar(progress_shape, nullptr, nullptr,
                            (float)m_progress_value, 0, (float)m_num_steps);
    m_next_frame = GuiButton(next_frame_shape, ">");
}

bool SequenceController::interact() {
    if (m_replay) {
        set_progress_value(0);
        set_run_all(true);
        return true;
    }

    if (m_prev_frame) {
        set_progress_value(std::max(get_progress_value() - 1, 0));
        return true;
    }

    if (m_next_frame) {
        set_progress_value(std::min(get_progress_value() + 1, m_num_steps));
        return true;
    }

    if (m_prev_speed) {
        m_speed = std::max(m_speed - 1, 2);
        return true;
    }

    if (m_next_speed) {
        m_speed = std::min(m_speed + 1, 6);
        return true;
    }

    return false;
}

}  // namespace component
