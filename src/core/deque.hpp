#ifndef CORE_DEQUE_HPP_
#define CORE_DEQUE_HPP_

#include "base_deque.hpp"

template<typename T>
class Deque : public BaseDeque<T> {
private:
    using Base = BaseDeque<T>;

public:
    using Base::Base;

    using Base::empty;
    using Base::size;

    using Base::push_back;
    using Base::push_front;

    using Base::back;
    using Base::front;

    using Base::pop_back;
    using Base::pop_front;
};

#endif  // CORE_DEQUE_HPP_
