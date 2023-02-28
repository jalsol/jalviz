#ifndef GUI_NODE_HPP_
#define GUI_NODE_HPP_

#include <array>
#include <cmath>
#include <string>

#include "constants.hpp"
#include "raylib.h"
#include "utils.hpp"

namespace gui {

template<typename T>
class Node {
private:
    T m_value{};

    Vector2 m_current_pos{};
    Vector2 m_target_pos{};

    bool m_is_outdated{false};

public:
    static constexpr int m_radius = 20;
    static constexpr float m_eps = 1e-3;

    explicit Node(const T& value);

    void render();
    void set_target_pos(Vector2 pos);
    [[nodiscard]] Vector2 get_target_pos() const;
    [[nodiscard]] Vector2 get_current_pos() const;
    [[nodiscard]] bool check_outdated() const;
};

template<typename T>
Node<T>::Node(const T& value) : m_value{value} {}

template<typename T>
void Node<T>::render() {
    if (m_is_outdated) {
        float diff_x = m_target_pos.x - m_current_pos.x;
        float diff_y = m_target_pos.y - m_current_pos.y;

        if (std::fabs(diff_x) < m_eps) {
            diff_x = 0;
        }

        if (std::fabs(diff_y) < m_eps) {
            diff_y = 0;
        }

        if (diff_x == 0 && diff_y == 0) {
            m_is_outdated = false;
        } else {
            m_current_pos.x +=
                diff_x / constants::frames_per_second * constants::ani_speed;
            m_current_pos.y +=
                diff_y / constants::frames_per_second * constants::ani_speed;
        }
    }

    constexpr int label_font_size = 25;
    constexpr int label_font_spacing = 2;
    const std::string label = std::to_string(m_value);

    const Vector2 label_size =
        utils::MeasureText(label.c_str(), label_font_size, label_font_spacing);

    const Vector2 label_pos{m_current_pos.x - label_size.x / 2,
                            m_current_pos.y - label_size.y / 2};

    DrawCircleV(m_current_pos, m_radius, BLACK);
    utils::DrawText(label.c_str(), label_pos, WHITE, label_font_size,
                    label_font_spacing);
}

template<typename T>
void Node<T>::set_target_pos(Vector2 pos) {
    m_target_pos = pos;
    m_is_outdated = true;
}

template<typename T>
Vector2 Node<T>::get_target_pos() const {
    return m_target_pos;
}

template<typename T>
Vector2 Node<T>::get_current_pos() const {
    return m_current_pos;
}

template<typename T>
bool Node<T>::check_outdated() const {
    return m_is_outdated;
}

}  // namespace gui

#endif  // GUI_NODE_HPP_
