#ifndef GUI_QUEUE_GUI_HPP_
#define GUI_QUEUE_GUI_HPP_

#include <cstddef>
#include <iostream>

#include "base_gui.hpp"
#include "constants.hpp"
#include "core/queue.hpp"
#include "node_gui.hpp"
#include "raylib.h"

namespace gui {

template<typename T>
class Queue : public core::Queue<Node<T>>, public internal::Base<T> {
private:
    using Base = core::Queue<Node<T>>;

    static constexpr Vector2 head_pos{
        constants::sidebar_width +
            (constants::scene_width - constants::sidebar_width) / 2.0F -
            15 * Node<T>::radius,
        constants::scene_height / 2.0F};

    using Base::m_head;
    using Base::m_tail;

    void render_link(Vector2 src, Vector2 dest) override;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    void push(const T& elem);
    void pop();

    void update() override;
    void render() override;
};

template<typename T>
void Queue<T>::push(const T& elem) {
    Base::push(Node<T>{elem});
}

template<typename T>
void Queue<T>::pop() {
    Base::pop();
}

template<typename T>
void Queue<T>::render_link(Vector2 src, Vector2 dest) {
    constexpr int radius = Node<T>::radius;
    constexpr float scaled_len = radius / 8.0F;

    // straight line
    Vector2 link_pos{src.x + radius, src.y - scaled_len};
    Vector2 link_size{dest.x - src.x - 2 * radius, 2 * scaled_len};

    // arrow
    constexpr int arrow_size = scaled_len * 5;
    Vector2 head{dest.x - radius + scaled_len / 2, src.y};
    Vector2 side_top{head.x - arrow_size, head.y - arrow_size};
    Vector2 side_bot{head.x - arrow_size, head.y + arrow_size};

    // draw both
    DrawRectangleV(link_pos, link_size, RED);
    DrawTriangle(head, side_top, side_bot, BLUE);
}

template<typename T>
void Queue<T>::render() {
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
void Queue<T>::update() {
    // TODO: if not outdated then return

    std::size_t pos = 0;

    for (auto* ptr = m_head; ptr != nullptr; ptr = ptr->next) {
        ptr->data.set_target_pos(
            {head_pos.x + 4 * Node<T>::radius * pos, head_pos.y});
        ++pos;
    }
}

}  // namespace gui

#endif  // GUI_QUEUE_GUI_HPP_
