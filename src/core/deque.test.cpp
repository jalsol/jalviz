#include "deque.hpp"

#include <array>
#include <initializer_list>

#include "doctest.h"

TEST_CASE("core::Deque functionality") {
    core::Deque<int> deque;
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

    deque.front() += 3;
    CHECK(deque.front() == 5);

    deque.push_back(0);
    deque.back() -= 2;
    CHECK(deque.back() == -2);
}

constexpr std::array<int, 3> list{1, 2, 3};

inline __attribute__((always_inline)) void check_match(core::Deque<int> deque) {
    for (int elem : list) {
        CHECK(deque.front() == elem);
        deque.pop_front();
    }
}

TEST_CASE("core::Deque special member functions") {
    std::initializer_list<int> init_list{1, 2, 3};

    SUBCASE("core::Deque(std::initializer_list<T>)") {
        core::Deque<int> deque{init_list};
        check_match(deque);
    }

    SUBCASE("core::Deque(const core::Deque&)") {
        core::Deque<int> deque1{init_list};
        core::Deque<int> deque2{deque1};  // NOLINT

        check_match(deque2);
        check_match(deque1);
    }

    SUBCASE("core::Deque& operator=(const core::Deque&) (single)") {
        core::Deque<int> deque1{init_list};
        core::Deque<int> deque2 = deque1;  // NOLINT

        check_match(deque2);
        check_match(deque1);
    }

    SUBCASE("core::Deque& operator=(const core::Deque&) (multiple)") {
        core::Deque<int> deque1{init_list};
        core::Deque<int> deque2;
        core::Deque<int> deque3;
        deque3 = deque2 = deque1;

        check_match(deque3);
        check_match(deque2);
        check_match(deque1);
    }

    SUBCASE("core::Deque(core::Deque&& rhs)") {
        {
            core::Deque<int> deque1{core::Deque<int>{init_list}};
            check_match(deque1);
        }
        {
            core::Deque<int> deque1{init_list};
            core::Deque<int> deque2{std::move(deque1)};
            check_match(deque2);
            CHECK(deque1.empty());  // NOLINT
        }
    }

    SUBCASE("core::Deque& operator=(core::Deque&& rhs)") {
        {
            core::Deque<int> deque1{1, 2, 3};
            core::Deque<int> deque2 = std::move(deque1);

            check_match(deque2);
            CHECK(deque1.empty());  // NOLINT
        }
        {
            core::Deque<int> deque{init_list};
            deque = std::move(deque);
            check_match(deque);  // NOLINT
        }
    }
}
