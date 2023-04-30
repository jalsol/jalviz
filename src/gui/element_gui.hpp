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

/**
 * @brief The GUI element (used in arrays)
 * @tparam T the type of the element
 */

template<typename T>
class GuiElement {
public:
    /**
     * @brief The side length of the element
     */
    static constexpr int side = 20;

    /**
     * @brief The initial position of the element
     */
    static constexpr Vector2 init_pos{
        constants::sidebar_width +
            static_cast<float>(constants::scene_width -
                               constants::sidebar_width) /
                2,
        0};

    /**
     * @brief Construct a new GuiElement object
     */
    GuiElement() = default;

    /**
     * @brief Construct a new GuiElement object
     * @param value The value of the element
     * @param index The index of the element
     */
    GuiElement(const T& value, std::size_t index);

    /**
     * @brief Renders the element
     */
    void render();

    /**
     * @brief Sets the position of the element
     * @param pos The position of the element
     */
    void set_pos(Vector2 pos);

    /**
     * @brief Sets the color index of the element
     * @param color_index The index of the color in the settings
     */
    void set_color_index(int color_index);

    /**
     * @brief Returns the position of the element
     * @return The position of the element
     */
    [[nodiscard]] Vector2 get_pos() const;

    /**
     * @brief Returns the reference to the value of the element
     * @return The reference to the value of the element
     */
    T& get_value();

    /**
     * @brief Returns the value of the element
     * @return The value of the element
     */
    T get_value() const;

    /**
     * @brief Set the value of the element
     * @param value The value of the element
     */
    void set_value(const T& value);

    /**
     * @brief Set the index of the element
     * @param index The index of the element
     */
    void set_index(std::size_t index);

private:
    /**
     * @brief The value of the element
     */
    T m_value{};

    /**
     * @brief The index of the element
     */
    std::size_t m_index{};

    /**
     * @brief The position of the element
     */
    Vector2 m_pos{init_pos};

    /**
     * @brief The epsilon for comparing floating point numbers
     */
    static constexpr float eps = 1e-3;

    /**
     * @brief The index of the color in the settings
     */
    int m_color_index{1};
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
