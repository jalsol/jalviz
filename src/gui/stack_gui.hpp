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

template<typename T>
class GuiStack : public core::Stack<GuiNode<T>>, public internal::Base {
private:
    using Base = core::Stack<GuiNode<T>>;

    static constexpr Vector2 head_pos{
        constants::scene_width / 2.0F - GuiNode<T>::radius / 2.0F,
        GuiNode<T>::radius * 4.0F};

    using Base::m_head;
    using Base::m_tail;

    void render_link(Vector2 src, Vector2 dest) override;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    GuiStack(std::initializer_list<GuiNode<T>> init_list);

    void push(const T& elem);
    void pop();

    void update() override;
    void render() override;
    void init_label();
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
