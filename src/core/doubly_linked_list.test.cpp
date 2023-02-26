#include "doubly_linked_list.hpp"

#include <iostream>

#include "doctest.h"

TEST_CASE("core::DoublyLinkedList functionality") {
    // List: {1, 2, 3}
    SUBCASE("Node_ptr search(const T& elem)") {
        core::DoublyLinkedList<int> dll{1, 2, 3};
        CHECK(dll.search(4) == nullptr);
        CHECK(dll.search(3)->data == 3);
    }

    // List: {1, 2, 3}
    SUBCASE("Node_ptr find(std::size_t index)") {
        core::DoublyLinkedList<int> dll{1, 2, 3};
        CHECK(dll.find(8) == nullptr);

        auto* ptr1 = dll.search(3);
        auto* ptr2 = dll.find(1);

        CHECK(ptr1->data == 3);
        CHECK(ptr2->data == 2);

        CHECK(ptr1->prev == ptr2);
        CHECK(ptr2->next == ptr1);
    }

    SUBCASE("Node_ptr insert(std::size_t index, const T& elem)") {
        core::DoublyLinkedList<int> dll{1, 2, 3};
        auto* ptr0 = dll.search(1);

        // List: {-1, 1, 2, 3}
        auto* ptr = dll.insert(0, -1);

        CHECK(dll.size() == 4);
        CHECK(ptr->next == ptr0);

        auto* ptrN = dll.search(3);
        // List: {-1, 1, 2, 3, 4}
        ptr = dll.insert(4, 4);

        CHECK(dll.size() == 5);
        CHECK(ptr->prev == ptrN);

        // List: {-1, 1, 20, 2, 3, 4}
        ptr = dll.insert(2, 20);  // NOLINT
        CHECK(ptr->prev == dll.find(1));
        CHECK(ptr->next == dll.find(3));
        CHECK(dll.size() == 6);

        // List: {-1, 1, 20, 2, 3, 4, 69}
        dll.insert(69, 69);  // NOLINT
        CHECK(dll.search(69) == dll.find(6));
        CHECK(dll.size() == 7);
    }

    // List: {-1, 1, 20, 2, 3, 4, 69}
    SUBCASE("Node_ptr remove(std::size_t index)") {
        core::DoublyLinkedList<int> dll{-1, 1, 20, 2, 3, 4, 69};  // NOLINT

        CHECK(dll.remove(1000) == nullptr);
        CHECK(dll.size() == 7);

        // List: {-1, 1, 20, 2, 3, 4}
        CHECK(dll.remove(6) == nullptr);
        CHECK(dll.size() == 6);

        // List: {1, 20, 2, 3, 4}
        auto* ptr = dll.remove(0);
        CHECK(dll.size() == 5);
        CHECK(ptr->data == 1);

        // List: {1, 2, 3, 4}
        ptr = dll.remove(1);
        CHECK(dll.size() == 4);
        CHECK(ptr->data == 2);
    }
}
