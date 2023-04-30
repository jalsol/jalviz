#ifndef GUI_STACK_GUI_HPP_
#define GUI_STACK_GUI_HPP_

#include <cstddef>
#include <iostream>

#include "base_gui.hpp"
#include "constants.hpp"
#include "core/stack.hpp"
#include "node_gui.hpp"
#include "raylib.h"
#include "settings.hpp"

namespace gui {

/**
 * @brief The GUI stack container
 * @tparam T the type of the elements
 */

template<typename T>
class GuiStack : public core::Stack<GuiNode<T>>, public internal::Base {
private:
    using Base = core::Stack<GuiNode<T>>;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    /**
     * @brief Construct a new Gui Stack object
     * @param init_list The initializer list
     */
    GuiStack(std::initializer_list<GuiNode<T>> init_list);

    /**
     * @brief Pushes an element to the top of the stack
     * @param elem The element
     */
    void push(const T& elem);

    /**
     * @brief Pops an element from the top of the stack
     */
    void pop();

    /**
     * @brief Updates the GUI stack
     */
    void update() override;

    /**
     * @brief Renders the GUI stack
     */
    void render() override;

    /**
     * @brief Initializes the labels
     */
    void init_label();

private:
    /**
     * @brief The position of the head
     */
    static constexpr Vector2 head_pos{
        constants::scene_width / 2.0F - GuiNode<T>::radius / 2.0F,
        GuiNode<T>::radius * 4.0F};

    using Base::m_head;
    using Base::m_tail;

    /**
     * @brief Renders a link between two nodes
     * @param src The source node
     * @param dest The destination node
     */
    void render_link(Vector2 src, Vector2 dest) override;
};

template<typename T>
void GuiStack<T>::init_label() {
    if (m_head != nullptr) {
        m_head->data.set_label("head");
    }
}

template<typename T>
GuiStack<T>::GuiStack(std::initializer_list<GuiNode<T>> init_list)
    : core::Stack<GuiNode<T>>(init_list) {
    init_label();
}

template<typename T>
void GuiStack<T>::push(const T& elem) {
    Base::push(GuiNode<T>{elem});
}

template<typename T>
void GuiStack<T>::pop() {
    Base::pop();
}

template<typename T>
void GuiStack<T>::render_link(Vector2 src, Vector2 dest) {
    constexpr int radius = GuiNode<T>::radius;
    constexpr float scaled_len = radius / 8.0F;

    // straight line
    Vector2 link_pos{src.x - scaled_len, src.y + radius};
    Vector2 link_size{2 * scaled_len, dest.y - src.y - 2 * radius};

    // arrow
    constexpr int arrow_size = scaled_len * 5;
    Vector2 head{src.x, dest.y - radius + scaled_len / 2};
    Vector2 side_left{head.x - arrow_size, head.y - arrow_size};
    Vector2 side_right{head.x + arrow_size, head.y - arrow_size};

    // draw both
    DrawRectangleV(link_pos, link_size, Settings::get_instance().get_color(1));
    DrawTriangle(head, side_right, side_left,
                 Settings::get_instance().get_color(1));
}

template<typename T>
void GuiStack<T>::render() {
    update();

    for (auto* ptr = m_head; ptr != nullptr; ptr = ptr->next) {
        if (ptr->next != nullptr) {
            render_link(ptr->data.get_pos(), ptr->next->data.get_pos());
        }

        ptr->data.render();
    }
}

template<typename T>
void GuiStack<T>::update() {
    // TODO: if not outdated then return

    std::size_t pos = 0;

    for (auto* ptr = m_head; ptr != nullptr; ptr = ptr->next) {
        ptr->data.set_pos(
            {head_pos.x, head_pos.y + 4 * GuiNode<T>::radius * pos});
        ++pos;
    }
}

}  // namespace gui

#endif  // GUI_STACK_GUI_HPP_
