#ifndef GUI_ELEMENT_GUI_HPP_
#define GUI_ELEMENT_GUI_HPP_

#include <array>
#include <cmath>
#include <iostream>
#include <string>

#include "constants.hpp"
#include "raylib.h"
#include "settings.hpp"
#include "utils.hpp"

namespace gui {

template<typename T>
class GuiElement {
private:
    T m_value{};
    std::size_t m_index{};

    Vector2 m_pos{init_pos};
    static constexpr float eps = 1e-3;
    int m_color_index{1};

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
    void set_pos(Vector2 pos);
    void set_color_index(int color_index);
    [[nodiscard]] Vector2 get_pos() const;

    T& get_value();
    T get_value() const;
    void set_value(const T& value);
    void set_index(std::size_t index);
};

template<typename T>
GuiElement<T>::GuiElement(const T& value, std::size_t index)
    : m_value{value}, m_index{index} {}

template<typename T>
void GuiElement<T>::render() {
    constexpr int label_font_size = 25;
    constexpr int label_font_spacing = 2;
    const std::string label = std::to_string(m_value);
    const std::string index = std::to_string(m_index);
    const Settings& settings = Settings::get_instance();

    const Vector2 label_size =
        utils::MeasureText(label.c_str(), label_font_size, label_font_spacing);

    const Vector2 label_pos{m_pos.x - label_size.x / 2,
                            m_pos.y - label_size.y / 2};

    const Vector2 index_size =
        utils::MeasureText(index.c_str(), label_font_size, label_font_spacing);

    const Vector2 index_pos{m_pos.x - index_size.x / 2,
                            m_pos.y - 2 * side - index_size.y / 2};

    const Color value_color =
        utils::adaptive_text_color(settings.get_color(m_color_index));
    const Color index_color =
        utils::adaptive_text_color(settings.get_color(Settings::num_color - 1));

    DrawRectangle(m_pos.x - side,  // NOLINT
                  m_pos.y - side,  // NOLINT
                  2 * side, 2 * side, settings.get_color(m_color_index));

    utils::DrawText(label.c_str(), label_pos, value_color, label_font_size,
                    label_font_spacing);

    utils::DrawText(index.c_str(), index_pos, index_color, label_font_size,
                    label_font_spacing);
}

template<typename T>
void GuiElement<T>::set_pos(Vector2 pos) {
    m_pos = pos;
}

template<typename T>
void GuiElement<T>::set_color_index(int color_index) {
    m_color_index = color_index;
}

template<typename T>
T& GuiElement<T>::get_value() {
    return m_value;
}

template<typename T>
T GuiElement<T>::get_value() const {
    return m_value;
}

template<typename T>
void GuiElement<T>::set_value(const T& value) {
    m_value = value;
}

template<typename T>
void GuiElement<T>::set_index(std::size_t index) {
    m_index = index;
}

}  // namespace gui

#endif  // GUI_ELEMENT_GUI_HPP_
