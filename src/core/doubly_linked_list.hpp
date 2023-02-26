#ifndef CORE_DOUBLY_LINKED_LIST_HPP_
#define CORE_DOUBLY_LINKED_LIST_HPP_

#include <cstddef>

#include "base_list.hpp"

namespace core {

template<typename T>
class DoublyLinkedList : public BaseList<T> {
private:
    using Base = BaseList<T>;
    using Node = typename Base::Node;
    using Node_ptr = Node*;
    using cNode_ptr = const Node*;

    using Base::m_head;
    using Base::m_size;
    using Base::m_tail;

    Node_ptr internal_search(const T& elem);
    Node_ptr internal_find(std::size_t index);

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    Node_ptr search(const T& elem);
    Node_ptr find(std::size_t index);

    cNode_ptr search(const T& elem) const;
    cNode_ptr find(std::size_t index) const;

    Node_ptr insert(std::size_t index, const T& elem);
    Node_ptr remove(std::size_t index);
};

template<typename T>
typename DoublyLinkedList<T>::Node_ptr DoublyLinkedList<T>::internal_search(
    const T& elem) {
    Node_ptr ptr{m_head};

    while (ptr != nullptr) {
        if (ptr->data == elem) {
            break;
        }

        ptr = ptr->next;
    }

    return ptr;
}

template<typename T>
typename DoublyLinkedList<T>::Node_ptr DoublyLinkedList<T>::internal_find(
    std::size_t index) {
    Node_ptr ptr{m_head};
    std::size_t pos = 0;

    while (ptr != nullptr && pos < index) {
        ptr = ptr->next;
        ++pos;
    }

    return ptr;
}

template<typename T>
typename DoublyLinkedList<T>::Node_ptr DoublyLinkedList<T>::search(
    const T& elem) {
    return internal_search(elem);
}

template<typename T>
typename DoublyLinkedList<T>::Node_ptr DoublyLinkedList<T>::find(
    std::size_t index) {
    return internal_find(index);
}

template<typename T>
typename DoublyLinkedList<T>::cNode_ptr DoublyLinkedList<T>::search(
    const T& elem) const {
    return internal_search(elem);
}

template<typename T>
typename DoublyLinkedList<T>::cNode_ptr DoublyLinkedList<T>::find(
    std::size_t index) const {
    return internal_find(index);
}

template<typename T>
typename DoublyLinkedList<T>::Node_ptr DoublyLinkedList<T>::insert(
    std::size_t index, const T& elem) {
    if (index == 0) {
        Base::push_front(elem);
        return m_head;
    }

    if (index + 1 >= m_size) {
        Base::push_back(elem);
        return m_tail;
    }

    Node_ptr ptr = find(index);
    auto new_node = new Node{elem, ptr->prev, ptr};

    ptr->prev->next = new_node;
    ptr->prev = new_node;
    ++m_size;

    return new_node;
}

template<typename T>
typename DoublyLinkedList<T>::Node_ptr DoublyLinkedList<T>::remove(
    std::size_t index) {
    if (index >= m_size) {
        return nullptr;
    }

    if (index == 0) {
        Base::pop_front();
        return m_head;
    }

    if (index + 1 == m_size) {
        Base::pop_back();
        return nullptr;
    }

    Node_ptr ptr = find(index);
    Node_ptr ret = ptr->next;

    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;

    delete ptr;
    --m_size;

    return ret;
}

}  // namespace core

#endif  // CORE_DOUBLY_LINKED_LIST_HPP_
