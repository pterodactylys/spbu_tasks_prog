#include "src/vector.hpp"
#include <iostream>

using abc::Vector;

int main() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.print();
}