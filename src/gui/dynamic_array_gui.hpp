#ifndef GUI_DYNAMIC_ARRAY_GUI_HPP_
#define GUI_DYNAMIC_ARRAY_GUI_HPP_

#include <array>
#include <cstddef>
#include <initializer_list>
#include <memory>

#include "base_gui.hpp"
#include "element_gui.hpp"
#include "raylib.h"
#include "settings.hpp"

namespace gui {

/**
 * @brief The GUI dynamic array container
 * @tparam T the type of the elements
 */

template<typename T>
class GuiDynamicArray : public internal::Base {
public:
    /**
     * @brief Constructs a GUI dynamic array
     */
    GuiDynamicArray();

    /**
     * @brief Constructs a GUI dynamic array with the specified initializer list
     * @param init_list The initializer list
     */
    GuiDynamicArray(std::initializer_list<T> init_list);

    /**
     * @brief Constructs a GUI dynamic array by coping another GUI dynamic array
     * @param other The other GUI dynamic array
     */
    GuiDynamicArray(const GuiDynamicArray& other);

    /**
     * @brief Constructs a GUI dynamic array by moving another GUI dynamic array
     * @param other The other GUI dynamic array
     */
    GuiDynamicArray(GuiDynamicArray&& other) noexcept;

    /**
     * @brief Assigns another GUI dynamic array to this GUI dynamic array by
     * copying
     * @param other The other GUI dynamic array
     * @return This GUI dynamic array
     */
    GuiDynamicArray& operator=(const GuiDynamicArray& other);

    /**
     * @brief Assigns another GUI dynamic array to this GUI dynamic array by
     * moving
     * @param other The other GUI dynamic array
     * @return This GUI dynamic array
     */
    GuiDynamicArray& operator=(GuiDynamicArray&& other) noexcept;

    /**
     * @brief Destructs the GUI dynamic array
     */
    ~GuiDynamicArray() override;

    /**
     * @brief Updates the GUI dynamic array
     */
    void update() override;

    /**
     * @brief Renders the GUI dynamic array
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
     * @param idx The index of the element
     * @param color_index The index of the color in the settings
     */
    void set_color_index(std::size_t idx, int color_index);

    /**
     * @brief Reserves the array with specified capacity
     * @param capacity The capacity
     */
    void reserve(std::size_t capacity);

    /**
     * @brief Resizes the array capacity to the current size
     */
    void shrink_to_fit();

    /**
     * @brief Returns the capacity of the array
     * @return The capacity of the array
     */
    std::size_t capacity() const;

    /**
     * @brief Returns the size of the array
     * @return The size of the array
     */
    std::size_t size() const;

    /**
     * @brief Pushes the value to the end of the array
     * @param value The value to push
     */
    void push(const T& value);

    /**
     * @brief Pops the value from the end of the array
     */
    void pop();

private:
    /**
     * @brief The head position
     */
    static constexpr Vector2 head_pos{
        constants::scene_width / 2.0F - 15 * GuiElement<T>::side,
        constants::scene_height / 2.0F};

    /**
     * @brief The capacity of the array
     */
    std::size_t m_capacity{2};

    /**
     * @brief The size of the array
     */
    std::size_t m_size{};

    /**
     * @brief The pointer to the array
     */
    GuiElement<T>* m_ptr{nullptr};

    /**
     * @brief Renders the link between the specified elements
     * @param src The source position
     * @param dest The destination position
     */
    void render_link(Vector2 src, Vector2 dest) override;
};

template<typename T>
void GuiDynamicArray<T>::reserve(std::size_t capacity) {
    capacity = std::min(capacity, static_cast<std::size_t>(8));
    if (m_capacity > capacity) {
        return;
    }

    auto* new_ptr = static_cast<GuiElement<T>*>(
        ::operator new[](capacity * sizeof(GuiElement<T>)));
    for (auto i = 0; i < m_size; ++i) {
        ::new (&new_ptr[i]) GuiElement<T>(std::move(m_ptr[i]));
        m_ptr[i].~GuiElement<T>();
    }
    for (auto i = m_size; i < capacity; ++i) {
        ::new (&new_ptr[i]) GuiElement<T>();
        new_ptr[i].set_index(i);
    }

    ::operator delete[](m_ptr);
    m_ptr = new_ptr;
    m_capacity = capacity;
}

template<typename T>
void GuiDynamicArray<T>::shrink_to_fit() {
    if (m_capacity == m_size) {
        return;
    }

    auto* new_ptr = static_cast<GuiElement<T>*>(
        ::operator new[](m_size * sizeof(GuiElement<T>)));
    for (auto i = 0; i < m_size; ++i) {
        ::new (&new_ptr[i]) GuiElement<T>(std::move(m_ptr[i]));
    }
    for (auto i = 0; i < m_capacity; ++i) {
        m_ptr[i].~GuiElement<T>();
    }

    ::operator delete[](m_ptr);
    m_ptr = new_ptr;
    m_capacity = m_size;
}

template<typename T>
GuiDynamicArray<T>::GuiDynamicArray() : m_ptr{new GuiElement<T>[m_capacity]} {
    for (auto i = 0; i < m_capacity; ++i) {
        m_ptr[i].set_index(i);
    }
}

template<typename T>
GuiDynamicArray<T>::GuiDynamicArray(std::initializer_list<T> init_list)
    : m_size{init_list.size()}, m_ptr{new GuiElement<T>[m_capacity]} {
    reserve(m_size);

    for (std::size_t idx = 0; auto elem : init_list) {
        *(m_ptr + idx).set_value(elem);
        *(m_ptr + idx).set_color(Settings::get_instance().get_color(0));
    }
}

template<typename T>
GuiDynamicArray<T>::GuiDynamicArray(const GuiDynamicArray<T>& other)
    : m_capacity{other.m_capacity},
      m_size{other.m_size},
      m_ptr{new GuiElement<T>[m_capacity]} {
    for (auto i = 0; i < m_capacity; ++i) {
        m_ptr[i] = other.m_ptr[i];
    }
}

template<typename T>
GuiDynamicArray<T>::GuiDynamicArray(GuiDynamicArray<T>&& other) noexcept
    : m_capacity{other.m_capacity}, m_size{other.m_size}, m_ptr{other.m_ptr} {
    other.m_capacity = 0;
    other.m_size = 0;
    other.m_ptr = nullptr;
}

template<typename T>
GuiDynamicArray<T>& GuiDynamicArray<T>::operator=(
    const GuiDynamicArray<T>& other) {
    if (&other != this) {
        m_capacity = other.m_capacity;
        m_size = other.m_size;

        m_ptr = new GuiDynamicArray<T>[m_capacity];
        for (auto i = 0; i < m_capacity; ++i) {
            m_ptr[i] = other.m_ptr[i];
        }
    }

    return *this;
}

template<typename T>
GuiDynamicArray<T>& GuiDynamicArray<T>::operator=(
    GuiDynamicArray&& other) noexcept {
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_ptr = other.m_ptr;

    other.m_capacity = 0;
    other.m_size = 0;
    other.m_ptr = nullptr;

    return *this;
}

template<typename T>
GuiDynamicArray<T>::~GuiDynamicArray() {
    delete[] m_ptr;
}

template<typename T>
void GuiDynamicArray<T>::render_link(Vector2 src, Vector2 dest) {}

template<typename T>
void GuiDynamicArray<T>::render() {
    update();

    std::size_t idx = 0;

    for (std::size_t i = 0; i < m_capacity; ++i) {
        m_ptr[i].render();
    }
}

template<typename T>
void GuiDynamicArray<T>::update() {
    // TODO: if not outdated then return

    for (std::size_t i = 0; i < m_capacity; ++i) {
        m_ptr[i].set_pos(
            {head_pos.x + 4 * GuiElement<T>::side * i, head_pos.y});
    }
}

template<typename T>
T& GuiDynamicArray<T>::operator[](std::size_t idx) {
    return m_ptr[idx].get_value();
}

template<typename T>
T GuiDynamicArray<T>::operator[](std::size_t idx) const {
    return m_ptr[idx].get_value();
}

template<typename T>
void GuiDynamicArray<T>::set_color_index(std::size_t idx, int color_index) {
    m_ptr[idx].set_color_index(color_index);
}

template<typename T>
std::size_t GuiDynamicArray<T>::capacity() const {
    return m_capacity;
}

template<typename T>
std::size_t GuiDynamicArray<T>::size() const {
    return m_size;
}

template<typename T>
void GuiDynamicArray<T>::push(const T& value) {
    if (m_size == m_capacity) {
        reserve(std::max(m_capacity * 2, static_cast<std::size_t>(1)));
    }

    m_ptr[m_size].set_color_index(0);
    m_ptr[m_size].set_value(value);
    ++m_size;
}

template<typename T>
void GuiDynamicArray<T>::pop() {
    if (m_size >= 1) {
        m_ptr[m_size - 1].set_color_index(1);
        m_ptr[m_size - 1].set_value(0);
        --m_size;
    }
}

}  // namespace gui

#endif  // GUI_DYNAMIC_ARRAY_GUI_HPP_
