#include "deque.hpp"
#include "doctest.h"

#include <array>
#include <initializer_list>

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

TEST_CASE("Deque special member functions") {
    std::initializer_list<int> init_list{1, 2, 3};
    std::array<int, 3> list{1, 2, 3};

#define CHECK_MATCH_AND_CLEAR(deque) for (int i = 0; i < 3; ++i) { CHECK(deque.front() == list.at(i)); deque.pop_front(); } // NOLINT

    SUBCASE("Deque(std::initializer_list<T>)") {
        Deque<int> deque{init_list};
        CHECK_MATCH_AND_CLEAR(deque);
    }

    SUBCASE("Deque(const Deque&)") {
        Deque<int> deque1{init_list};
        Deque<int> deque2{deque1};

        CHECK_MATCH_AND_CLEAR(deque2);
        CHECK_MATCH_AND_CLEAR(deque1);
    }

    SUBCASE("Deque& operator=(const Deque&) (single)") {
        Deque<int> deque1{init_list};
        Deque<int> deque2 = deque1;

        CHECK_MATCH_AND_CLEAR(deque2);
        CHECK_MATCH_AND_CLEAR(deque1);
    }

    SUBCASE("Deque& operator=(const Deque&) (multiple)") {
        Deque<int> deque1{init_list};
        Deque<int> deque2;
        Deque<int> deque3;
        deque3 = deque2 = deque1;

        CHECK_MATCH_AND_CLEAR(deque3);
        CHECK_MATCH_AND_CLEAR(deque2);
        CHECK_MATCH_AND_CLEAR(deque1);
    }

    SUBCASE("Deque(Deque&& rhs)") {
        {
            Deque<int> deque1{Deque<int>{init_list}};
            CHECK_MATCH_AND_CLEAR(deque1);
        }
        {
            Deque<int> deque1{init_list};
            Deque<int> deque2{std::move(deque1)};
            CHECK_MATCH_AND_CLEAR(deque2);
            CHECK(deque1.empty());
        }
    }

    SUBCASE("Deque& operator=(Deque&& rhs)") {
        {
            Deque<int> deque1{1, 2, 3};
            Deque<int> deque2 = std::move(deque1);

            CHECK_MATCH_AND_CLEAR(deque2);
            CHECK(deque1.empty());
        }
        {
            Deque<int> deque{init_list};
            deque = std::move(deque);
            CHECK_MATCH_AND_CLEAR(deque);
        }
    }
#undef CHECK_MATCH_AND_CLEAR
}
