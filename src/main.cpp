#include <iostream>

#include "utils.hpp"

int main() {
    std::cout << "hi\n";
    std::cout << returnOne() << '\n';

    constexpr int num = 10;

    for (int i = 0; i < num; ++i) {
        std::cout << i << std::endl;
    }
}
