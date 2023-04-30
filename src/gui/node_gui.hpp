#ifndef GUI_NODE_GUI_HPP_
#define GUI_NODE_GUI_HPP_

#include <array>
#include <cmath>
#include <string>

#include "constants.hpp"
#include "raylib.h"
#include "settings.hpp"
#include "utils.hpp"

namespace gui {

/**
 * @brief The GUI node (used in linked lists)
 * @tparam T the type of the node
 */

template<typename T>
class GuiNode {
public:
    /**
     * @brief The radius of the node
     */
    static constexpr int radius = 20;

    /**
     * @brief Construct a new GuiNode object with the specified value
     */
    explicit GuiNode(const T& value);

    /**
     * @brief Renders the node
     */
    void render();

    /**
     * @brief Sets the position of the node
     * @param pos The position of the node
     */
    void set_pos(Vector2 pos);

    /**
     * @brief Gets the position of the node
     * @return The position of the node
     */
    [[nodiscard]] Vector2 get_pos() const;

    /**
     * @brief Sets the color index of the node
     * @param color_index The color index of the node in the settings
     */
    void set_color_index(int color_index);

    /**
     * @brief Sets the value of the node
     * @param value The value of the node
     */
    void set_value(const T& value);

    /**
     * @brief Returns the reference to the value of the node
     * @return T& The reference to the value of the node
     */
    T& get_value();

    /**
     * @brief Sets the label of the node
     * @param label The label of the node
     */
    void set_label(const char* label);

private:
    /**
     * @brief The value of the node
     */
    T m_value{};

    /**
     * @brief The color index of the node in the settings
     */
    int m_color_index{0};

    /**
     * @brief The position of the node
     */
    Vector2 m_pos{constants::sidebar_width +
                      static_cast<float>(constants::scene_width -
                                         constants::sidebar_width) /
                          2,
                  0};

    /**
     * @brief The epsilon used for comparing floats
     */
    static constexpr float eps = 1e-3;

    /**
     * @brief The label of the node
     */
    const char* m_label{};
};

template<typename T>
GuiNode<T>::GuiNode(const T& value) : m_value{value} {}

template<typename T>
void GuiNode<T>::render() {
    constexpr int label_font_size = 25;
    constexpr int label_font_spacing = 2;
    const std::string value = std::to_string(m_value);
    const Settings& settings = Settings::get_instance();

    const Vector2 value_size =
        utils::MeasureText(value.c_str(), label_font_size, label_font_spacing);

    const Vector2 value_pos{m_pos.x - value_size.x / 2,
                            m_pos.y - value_size.y / 2};

    const Vector2 label_size =
        utils::MeasureText(m_label, label_font_size, label_font_spacing);

    const Vector2 label_pos{m_pos.x - label_size.x / 2,
                            m_pos.y - 2 * label_size.y};

    const Color value_color =
        utils::adaptive_text_color(settings.get_color(m_color_index));

    DrawCircleV(m_pos, radius, settings.get_color(m_color_index));
    utils::DrawText(value.c_str(), value_pos, value_color, label_font_size,
                    label_font_spacing);

    utils::DrawText(m_label, label_pos, settings.get_color(5), label_font_size,
                    label_font_spacing);
}

template<typename T>
void GuiNode<T>::set_color_index(int color_index) {
    m_color_index = color_index;
}

template<typename T>
void GuiNode<T>::set_value(const T& value) {
    m_value = value;
}

template<typename T>
T& GuiNode<T>::get_value() {
    return m_value;
}

template<typename T>
void GuiNode<T>::set_pos(Vector2 pos) {
    m_pos = pos;
}

template<typename T>
Vector2 GuiNode<T>::get_pos() const {
    return m_pos;
}

template<typename T>
void GuiNode<T>::set_label(const char* label) {
    m_label = label;
}

}  // namespace gui

#endif  // GUI_NODE_GUI_HPP_
