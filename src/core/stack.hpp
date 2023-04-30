#ifndef CORE_STACK_HPP_
#define CORE_STACK_HPP_

#include "base_list.hpp"

namespace core {

/**
 * @brief The stack container
 * @tparam T the type of the elements
 */

template<typename T>
class Stack : public BaseList<T> {
private:
    using Base = BaseList<T>;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    /**
     * @brief Returns the reference to the top element of the stack
     * @return T& the reference to the top element of the stack
     */
    T& top() const;

    /**
     * @brief Inserts the element at the top of the stack
     * @param elem The element to insert
     */
    void push(const T& elem);

    /**
     * @brief Removes the top element of the stack
     */
    void pop();

protected:
    using Base::m_head;
    using Base::m_tail;
};

template<typename T>
T& Stack<T>::top() const {
    return Base::front();
}

template<typename T>
void Stack<T>::push(const T& elem) {
    Base::push_front(elem);
}

template<typename T>
void Stack<T>::pop() {
    Base::pop_front();
}

}  // namespace core

#endif  // CORE_STACK_HPP_
