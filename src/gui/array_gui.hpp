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

/**
 * @brief The GUI array container
 * @tparam T the type of the elements
 * @tparam N the number of elements
 */

template<typename T, std::size_t N>
class GuiArray : public internal::Base {
public:
    /**
     * @brief Constructs a GUI array with the specified number of elements
     */
    GuiArray();

    /**
     * @brief Constructs a GUI array with the specified initializer list
     * @param init_list The initializer list
     */
    GuiArray(std::array<GuiElement<T>, N>&& init_list);

    /**
     * @brief Updates the GUI array
     */
    void update() override;

    /**
     * @brief Renders the GUI array
     */
    void render() override;

    /**
     * @brief Returns the reference to the element at the specified index
     * @param idx The index of the element
     * @return The reference to the element at the specified index
     */
    T& operator[](std::size_t idx);

    /**
     * @brief Returns the value to the element at the specified index
     * @param idx The index of the element
     * @return The value to the element at the specified index
     */
    T operator[](std::size_t idx) const;

    /**
     * @brief Set the color index object
     *
     * @param idx The index of the element to color
     * @param color_index The index of the color in the settings
     */
    void set_color_index(std::size_t idx, int color_index);

private:
    /**
     * @brief The position of the head
     */
    static constexpr Vector2 head_pos{
        constants::scene_width / 2.0F - 15 * GuiElement<T>::side,
        constants::scene_height / 2.0F};

    /**
     * @brief The array of elements
     */
    std::array<GuiElement<T>, N> m_array{};

    /**
     * @brief Renders the link between the source and destination
     * @param src The source position
     * @param dest The destination position
     */
    void render_link(Vector2 src, Vector2 dest) override;
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
