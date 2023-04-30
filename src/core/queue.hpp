#ifndef CORE_QUEUE_HPP_
#define CORE_QUEUE_HPP_

#include "base_list.hpp"

namespace core {

/**
 * @brief The queue container
 * @tparam T the type of the elements
 */

template<typename T>
class Queue : public BaseList<T> {
private:
    using Base = BaseList<T>;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    /**
     * @note For animation purpose only, not for real use
     */
    using Base::pop_back;
    using Base::push_front;

    /**
     * @brief Returns the reference to the front element of the queue
     * @return T& the reference to the front element of the queue
     */
    T& front() const;

    /**
     * @brief Returns the reference to the back element of the queue
     * @return T& the reference to the back element of the queue
     */
    T& back() const;

    /**
     * @brief Inserts the element at the back of the queue
     * @param elem The element to insert
     */
    void push(const T& elem);

    /**
     * @brief Removes the front element of the queue
     */
    void pop();
};

template<typename T>
T& Queue<T>::front() const {
    return Base::front();
}

template<typename T>
T& Queue<T>::back() const {
    return Base::back();
}

template<typename T>
void Queue<T>::push(const T& elem) {
    Base::push_back(elem);
}

template<typename T>
void Queue<T>::pop() {
    Base::pop_front();
}

}  // namespace core

#endif  // CORE_QUEUE_HPP_
