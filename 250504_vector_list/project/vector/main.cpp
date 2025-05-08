#include "src/vector.hpp"
#include <iostream>

using abc::Vector;

int main() {
    Vector<int> vec;
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }
    Vector<int> vec2;
    vec2 = vec;
    vec2.push_back(6);
    vec2.print();
}