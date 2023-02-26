#ifndef CORE_QUEUE_HPP_
#define CORE_QUEUE_HPP_

#include "base_list.hpp"

namespace core {

template<typename T>
class Queue : public BaseList<T> {
private:
    using Base = BaseList<T>;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    T& front() const;

    void push(const T& elem);
    void pop();
};

template<typename T>
T& Queue<T>::front() const {
    return Base::front();
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
