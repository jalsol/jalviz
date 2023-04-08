#ifndef GUI_ARRAY_GUI_HPP_
#define GUI_ARRAY_GUI_HPP_

#include <array>
#include <cstddef>
#include <initializer_list>

#include "base_gui.hpp"
#include "element_gui.hpp"
#include "raylib.h"
#include "settings.hpp"

namespace gui {

template<typename T, std::size_t N>
class GuiArray : public internal::Base {
private:
    static constexpr Vector2 head_pos{
        constants::scene_width / 2.0F - 15 * GuiElement<T>::side,
        constants::scene_height / 2.0F};

    std::array<GuiElement<T>, N> m_array{};

    void render_link(Vector2 src, Vector2 dest) override;

public:
    GuiArray();
    GuiArray(std::array<GuiElement<T>, N>&& init_list);
    void update() override;
    void render() override;

    T& operator[](std::size_t idx);
    T operator[](std::size_t idx) const;

    void set_color_index(std::size_t idx, int color_index);
};

template<typename T, std::size_t N>
GuiArray<T, N>::GuiArray() {
    for (std::size_t i = 0; i < N; ++i) {
        m_array[i] = GuiElement<T>{0, i};
        m_array[i].set_color_index(0);
    }
}

template<typename T, std::size_t N>
GuiArray<T, N>::GuiArray(std::array<GuiElement<T>, N>&& init_list)
    : m_array{init_list} {}

template<typename T, std::size_t N>
void GuiArray<T, N>::render_link(Vector2 src, Vector2 dest) {}

template<typename T, std::size_t N>
void GuiArray<T, N>::render() {
    update();

    for (std::size_t i = 0; i < N; ++i) {
        m_array[i].render();
    }
}

template<typename T, std::size_t N>
void GuiArray<T, N>::update() {
    // TODO: if not outdated then return

    for (std::size_t i = 0; i < N; ++i) {
        m_array[i].set_pos(
            {head_pos.x + 4 * GuiElement<T>::side * i, head_pos.y});
    }
}

template<typename T, std::size_t N>
T& GuiArray<T, N>::operator[](std::size_t idx) {
    return m_array[idx].get_value();
}

template<typename T, std::size_t N>
T GuiArray<T, N>::operator[](std::size_t idx) const {
    return m_array[idx].get_value();
}

template<typename T, std::size_t N>
void GuiArray<T, N>::set_color_index(std::size_t idx, int color_index) {
    m_array[idx].set_color_index(color_index);
}

}  // namespace gui

#endif  // GUI_ARRAY_GUI_HPP_
