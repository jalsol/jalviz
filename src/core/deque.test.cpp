#include "deque.hpp"
#include "doctest.h"

TEST_CASE("Deque functionality") {
    Deque<int> deque;
    CHECK(deque.empty());

    deque.push_back(2);
    deque.push_back(3);
    deque.push_front(1);

    CHECK(deque.front() == 1);
    CHECK(deque.back() == 3);
    CHECK(deque.size() == 3);

    deque.pop_back();
    CHECK(deque.back() == 2);
    CHECK(deque.size() == 2);

    deque.pop_front();
    CHECK(deque.front() == 2);
    CHECK(deque.size() == 1);
}
