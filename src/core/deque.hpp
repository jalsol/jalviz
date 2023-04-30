#ifndef CORE_DEQUE_HPP_
#define CORE_DEQUE_HPP_

#include "base_list.hpp"

namespace core {

/**
 * @brief The deque container
 * @tparam T the type of the elements
 */

template<typename T>
class Deque : public BaseList<T> {
private:
    using Base = BaseList<T>;

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

}  // namespace core

#endif  // CORE_DEQUE_HPP_
