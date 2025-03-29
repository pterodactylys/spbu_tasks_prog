#include "print.hpp"

#include <iostream>

void tools::print_array(const char* const comment, const int* arr, const int size) {
	std::cout << comment << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}