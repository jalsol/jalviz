#include "deque.hpp"

#include <array>
#include <initializer_list>

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

constexpr std::array<int, 3> list{1, 2, 3};

inline __attribute__((always_inline)) void check_match(Deque<int> deque) {
    for (int elem : list) {
        CHECK(deque.front() == elem);
        deque.pop_front();
    }
}

TEST_CASE("Deque special member functions") {
    std::initializer_list<int> init_list{1, 2, 3};

    SUBCASE("Deque(std::initializer_list<T>)") {
        Deque<int> deque{init_list};
        check_match(deque);
    }

    SUBCASE("Deque(const Deque&)") {
        Deque<int> deque1{init_list};
        Deque<int> deque2{deque1};  // NOLINT

        check_match(deque2);
        check_match(deque1);
    }

    SUBCASE("Deque& operator=(const Deque&) (single)") {
        Deque<int> deque1{init_list};
        Deque<int> deque2 = deque1;  // NOLINT

        check_match(deque2);
        check_match(deque1);
    }

    SUBCASE("Deque& operator=(const Deque&) (multiple)") {
        Deque<int> deque1{init_list};
        Deque<int> deque2;
        Deque<int> deque3;
        deque3 = deque2 = deque1;

        check_match(deque3);
        check_match(deque2);
        check_match(deque1);
    }

    SUBCASE("Deque(Deque&& rhs)") {
        {
            Deque<int> deque1{Deque<int>{init_list}};
            check_match(deque1);
        }
        {
            Deque<int> deque1{init_list};
            Deque<int> deque2{std::move(deque1)};
            check_match(deque2);
            CHECK(deque1.empty());  // NOLINT
        }
    }

    SUBCASE("Deque& operator=(Deque&& rhs)") {
        {
            Deque<int> deque1{1, 2, 3};
            Deque<int> deque2 = std::move(deque1);

            check_match(deque2);
            CHECK(deque1.empty());  // NOLINT
        }
        {
            Deque<int> deque{init_list};
            deque = std::move(deque);
            check_match(deque);  // NOLINT
        }
    }
}
