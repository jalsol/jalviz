#ifndef COMPONENT_SEQUENCE_CONTROLLER_HPP_
#define COMPONENT_SEQUENCE_CONTROLLER_HPP_

#include "raylib.h"

namespace component {

class SequenceController {
private:
    static constexpr Vector2 button_size{25, 25};
    static constexpr int speed_scale = 4;

    bool m_replay{};
    bool m_prev_frame{};
    bool m_next_frame{};
    int m_progress_value{};
    int m_num_steps{};
    bool m_run_all{};
    int m_anim_counter{};

    bool m_prev_speed{};
    bool m_next_speed{};
    int m_speed{speed_scale};

public:
    void render();
    bool interact();

    void set_max_value(int num);
    void set_progress_value(int value);
    void set_run_all(bool run_all);
    void set_rerun();

    bool get_run_all() const;
    int get_progress_value() const;
    float get_speed_scale() const;

    void reset_anim_counter();
    void inc_anim_counter();
    int get_anim_counter() const;
    int get_anim_frame() const;
};

}  // namespace component

#endif  // COMPONENT_SEQUENCE_CONTROLLER_HPP_
