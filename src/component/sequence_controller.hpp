#ifndef COMPONENT_SEQUENCE_CONTROLLER_HPP_
#define COMPONENT_SEQUENCE_CONTROLLER_HPP_

#include "raylib.h"

namespace component {

/**
 * @brief Controls the display of frames of the animation sequence
 */

class SequenceController {
public:
    /**
     * @brief Renders the sequence controller
     */
    void render();

    /**
     * @brief Checks if the sequence controller was interacted with
     * @retval true The sequence controller was interacted with
     * @retval false The sequence controller was not interacted with
     */
    bool interact();

    /**
     * @brief Sets the maximum number of steps that can be accessed
     * @param num the maximum number of steps that can be accessed
     */
    void set_max_value(int num);

    /**
     * @brief Sets the value of the progress bar
     * @param value the value of the progress bar
     */
    void set_progress_value(int value);

    /**
     * @brief Sets the sequence to be in the run-all-at-once mode
     * @param run_all true if the sequence is in the run-all-at-once mode, false
     * otherwise
     */
    void set_run_all(bool run_all);

    /**
     * @brief Sets the sequence to rerun from the beginning
     */
    void set_rerun();

    /**
     * @brief Check if the sequence is in the run-all-at-once mode
     * @retval true The sequence is in the run-all-at-once mode
     * @retval false The sequence is not in the run-all-at-once mode
     */
    bool get_run_all() const;

    /**
     * @brief Gets the value of the progress bar
     * @return the value of the progress bar
     */
    int get_progress_value() const;

    /**
     * @brief Gets the speed scale of the sequence
     * @return the speed scale of the sequence
     */
    float get_speed_scale() const;

    /**
     * @brief Resets the animation counter
     */
    void reset_anim_counter();

    /**
     * @brief Increments the animation counter
     */
    void inc_anim_counter();

    /**
     * @brief Gets the animation counter
     * @return the animation counter
     */
    int get_anim_counter() const;

    /**
     * @brief Gets the animated frame
     * @return the animated frame
     */
    int get_anim_frame() const;

private:
    /**
     * @brief The size of the buttons
     */
    static constexpr Vector2 button_size{25, 25};

    /**
     * @brief The scale of the speed
     */
    static constexpr int speed_scale = 4;

    /**
     * @brief Whether the animation has to be replayed
     */
    bool m_replay{};

    /**
     * @brief Whether to move to the previous frame
     */
    bool m_prev_frame{};

    /**
     * @brief Whether to move to the next frame
     */
    bool m_next_frame{};

    /**
     * @brief The value of the progress bar
     */
    int m_progress_value{};

    /**
     * @brief The maximum number of steps that can be accessed
     */
    int m_num_steps{};

    /**
     * @brief Whether the sequence is in the run-all-at-once mode
     */
    bool m_run_all{};

    /**
     * @brief The animation counter
     */
    int m_anim_counter{};

    /**
     * @brief Whether to slow down the animation
     */
    bool m_prev_speed{};

    /**
     * @brief Whether to speed up the animation
     */
    bool m_next_speed{};

    /**
     * @brief The scaled speed of the sequence
     */
    int m_speed{speed_scale};
};

}  // namespace component

#endif  // COMPONENT_SEQUENCE_CONTROLLER_HPP_
