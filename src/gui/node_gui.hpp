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

template<typename T>
class GuiNode {
private:
    T m_value{};
    int m_color_index{0};

    Vector2 m_pos{constants::sidebar_width +
                      static_cast<float>(constants::scene_width -
                                         constants::sidebar_width) /
                          2,
                  0};
    static constexpr float eps = 1e-3;
    const char* m_label{};

public:
    static constexpr int radius = 20;

    explicit GuiNode(const T& value);

    void render();
    void set_pos(Vector2 pos);
    [[nodiscard]] Vector2 get_pos() const;
    void set_color_index(int color_index);
    void set_value(const T& value);
    T& get_value();
    void set_label(const char* label);
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
        utils::adaptive_text_color(Settings::get_instance().get_color(0));

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
