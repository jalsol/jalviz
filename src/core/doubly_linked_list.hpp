#ifndef CORE_DOUBLY_LINKED_LIST_HPP_
#define CORE_DOUBLY_LINKED_LIST_HPP_

#include <cstddef>

#include "base_list.hpp"

namespace core {

/**
 * @brief The doubly linked list container
 * @tparam T the type of the elements
 */

template<typename T>
class DoublyLinkedList : public BaseList<T> {
protected:
    using Base = BaseList<T>;
    using Node = typename Base::Node;
    using Node_ptr = Node*;
    using cNode_ptr = const Node*;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    /**
     * @brief Searches for the element in the container
     * @param elem The element to search for
     * @return The pointer to the element if found, nullptr otherwise
     */
    Node_ptr search(const T& elem);

    /**
     * @brief Finds the element at the specified index
     * @param index The index of the element
     * @return The pointer to the element if found, nullptr otherwise
     */
    Node_ptr find(std::size_t index);

    /**
     * @brief Searches for the element in the container
     * @param elem The element to search for
     * @return The const pointer to the element if found, nullptr otherwise
     */
    cNode_ptr search(const T& elem) const;

    /**
     * @brief Finds the element at the specified index
     * @param index The index of the element
     * @return The const pointer to the element if found, nullptr otherwise
     */
    cNode_ptr find(std::size_t index) const;

    /**
     * @brief Inserts the element at the specified index
     * @param index The index of the element
     * @param elem The element to insert
     * @return The pointer to the inserted element
     */
    Node_ptr insert(std::size_t index, const T& elem);

    /**
     * @brief Removes the element at the specified index
     * @param index The index of the element
     * @return The pointer to the removed element
     */
    Node_ptr remove(std::size_t index);

    /**
     * @brief Gets the element at the specified index
     * @param index The index of the element
     * @return T& The reference to the element
     */
    T& at(std::size_t index);

    /**
     * @brief Gets the element at the specified index
     * @param index The index of the element
     * @return T The copy of the element
     */
    T at(std::size_t index) const;

    /**
     * @brief Clears the container
     */
    void clear();

protected:
    using Base::m_head;
    using Base::m_size;
    using Base::m_tail;

    /**
     * @brief Internal method to search for the element in the container
     * @param elem The element to search for
     * @return The pointer to the element if found, nullptr otherwise
     */
    Node_ptr internal_search(const T& elem);

    /**
     * @brief Internal method to find the element at the specified index
     * @param index The index of the element
     * @return The pointer to the element if found, nullptr otherwise
     */
    Node_ptr internal_find(std::size_t index);
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

    if (index >= m_size) {
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

template<typename T>
T& DoublyLinkedList<T>::at(std::size_t index) {
    return find(index)->data;
}

template<typename T>
T DoublyLinkedList<T>::at(std::size_t index) const {
    return find(index)->data;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    while (!empty()) {
        Base::pop_front();
    }
}

}  // namespace core

#endif  // CORE_DOUBLY_LINKED_LIST_HPP_
