#ifndef GUI_STACK_HPP_
#define GUI_STACK_HPP_

#include <cstddef>
#include <iostream>

#include "base.hpp"
#include "constants.hpp"
#include "core/stack.hpp"
#include "node.hpp"
#include "raylib.h"

namespace gui {

template<typename T>
class Stack : public core::Stack<Node<T>>, public internal::Base<T> {
private:
    using Base = core::Stack<Node<T>>;

    static constexpr Vector2 m_head_pos{
        constants::scene_width / 2.0F - Node<T>::m_radius / 2.0F,
        Node<T>::m_radius * 4};

    using Base::m_head;
    using Base::m_tail;

    // using Base::top;
    // using Base::push;
    // using Base::pop;

    void render_link(Vector2 src, Vector2 dest) override;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    // T& top() const;

    // void push(const T& elem);
    // void pop();

    void update() override;
    void render() override;
};

// template<typename T>
// T& Stack<T>::top() const {
//     return Base::top();
// }

// template<typename T>
// void Stack<T>::push(const T& elem) {
//     Base::push(elem);
// }

// template<typename T>
// void Stack<T>::pop() {
//     Base::pop();
// }

template<typename T>
void Stack<T>::render_link(Vector2 src, Vector2 dest) {
    constexpr int radius = Node<T>::m_radius;
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
    DrawRectangleV(link_pos, link_size, RED);
    DrawTriangle(head, side_right, side_left, BLUE);
}

template<typename T>
void Stack<T>::render() {
    update();

    for (auto* ptr = m_head; ptr != nullptr; ptr = ptr->next) {
        if (ptr->next != nullptr) {
            render_link(ptr->data.get_current_pos(),
                        ptr->next->data.get_current_pos());
        }

        ptr->data.render();
    }
}

template<typename T>
void Stack<T>::update() {
    // TODO: if not outdated then return

    std::size_t pos = 0;

    for (auto* ptr = m_head; ptr != nullptr; ptr = ptr->next) {
        ++pos;
        ptr->data.set_target_pos(
            {m_head_pos.x, m_head_pos.y * static_cast<float>(pos)});
    }
}

}  // namespace gui

#endif  // GUI_STACK_HPP_
