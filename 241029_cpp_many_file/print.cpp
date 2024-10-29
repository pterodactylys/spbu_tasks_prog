#include "print.hpp"

#include <iostream>

void tools::print_array(const int* arr, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}