#include "src/vector.hpp"
#include <iostream>

using abc::Vector;

int main() {
    Vector<int> vec;
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }
    for (int i = 0; i < 990; ++i) {
        vec.remove_first(i);
    }
    size_t size = vec.get_size();
    size_t capacity = vec.get_capacity();
    std::cout << "Size: " << size << ", Capacity: " << capacity << std::endl;
}