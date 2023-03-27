#ifndef GUI_ELEMENT_GUI_HPP_
#define GUI_ELEMENT_GUI_HPP_

#include <array>
#include <cmath>
#include <iostream>
#include <string>

#include "constants.hpp"
#include "raylib.h"
#include "utils.hpp"

namespace gui {

template<typename T>
class GuiElement {
private:
    T m_value{};
    std::size_t m_index{};

    Vector2 m_current_pos{init_pos};
    Vector2 m_target_pos{};
    bool m_is_outdated{false};
    static constexpr float eps = 1e-3;
    Color m_color{BLACK};

public:
    static constexpr int side = 20;
    static constexpr Vector2 init_pos{
        constants::sidebar_width +
            static_cast<float>(constants::scene_width -
                               constants::sidebar_width) /
                2,
        0};

    GuiElement() = default;
    GuiElement(const T& value, std::size_t index);

    void render();
    void set_target_pos(Vector2 pos);
    void set_color(Color color);
    [[nodiscard]] Vector2 get_target_pos() const;
    [[nodiscard]] Vector2 get_current_pos() const;
    [[nodiscard]] bool check_outdated() const;

    T& get_value();
    T get_value() const;
};

template<typename T>
GuiElement<T>::GuiElement(const T& value, std::size_t index)
    : m_value{value}, m_index{index} {}

template<typename T>
void GuiElement<T>::render() {
    if (m_is_outdated) {
        float diff_x = m_target_pos.x - m_current_pos.x;
        float diff_y = m_target_pos.y - m_current_pos.y;

        if (std::fabs(diff_x) < eps) {
            diff_x = 0;
        }

        if (std::fabs(diff_y) < eps) {
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
    const std::string index = std::to_string(m_index);

    const Vector2 label_size =
        utils::MeasureText(label.c_str(), label_font_size, label_font_spacing);

    const Vector2 label_pos{m_current_pos.x - label_size.x / 2,
                            m_current_pos.y - label_size.y / 2};

    const Vector2 index_size =
        utils::MeasureText(index.c_str(), label_font_size, label_font_spacing);

    const Vector2 index_pos{m_current_pos.x - index_size.x / 2,
                            m_current_pos.y - 2 * side - index_size.y / 2};

    DrawRectangle(m_current_pos.x - side,  // NOLINT
                  m_current_pos.y - side,  // NOLINT
                  2 * side, 2 * side, m_color);

    utils::DrawText(label.c_str(), label_pos, WHITE, label_font_size,
                    label_font_spacing);

    utils::DrawText(index.c_str(), index_pos, BLACK, label_font_size,
                    label_font_spacing);
}

template<typename T>
void GuiElement<T>::set_target_pos(Vector2 pos) {
    m_target_pos = pos;
    m_is_outdated = true;
}

template<typename T>
void GuiElement<T>::set_color(Color color) {
    m_color = color;
}

template<typename T>
Vector2 GuiElement<T>::get_target_pos() const {
    return m_target_pos;
}

template<typename T>
Vector2 GuiElement<T>::get_current_pos() const {
    return m_current_pos;
}

template<typename T>
bool GuiElement<T>::check_outdated() const {
    return m_is_outdated;
}

template<typename T>
T& GuiElement<T>::get_value() {
    return m_value;
}

template<typename T>
T GuiElement<T>::get_value() const {
    return m_value;
}

}  // namespace gui

#endif  // GUI_ELEMENT_GUI_HPP_
