#ifndef CORE_STACK_HPP_
#define CORE_STACK_HPP_

#include "base_list.hpp"

namespace core {

template<typename T>
class Stack : public BaseList<T> {
private:
    using Base = BaseList<T>;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    T& top() const;

    void push(const T& elem);
    void pop();
};

template<typename T>
T& Stack<T>::top() const {
    return Base::back();
}

template<typename T>
void Stack<T>::push(const T& elem) {
    Base::push_back(elem);
}

template<typename T>
void Stack<T>::pop() {
    Base::pop_back();
}

}  // namespace core

#endif  // CORE_STACK_HPP_
