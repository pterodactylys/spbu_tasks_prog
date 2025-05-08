#include "src/vector.hpp"
#include <iostream>

using abc::Vector;

int main() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.insert(1, 4);
    vec.insert(0, 5);
    Vector<int> vec2;
    vec2 = vec;
    vec2.push_back(6);
    vec2.print();
}