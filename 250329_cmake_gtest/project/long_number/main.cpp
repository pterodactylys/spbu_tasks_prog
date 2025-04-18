#include "src/long_number.hpp"
#include <iostream>

using abc::LongNumber;

int main() {
    abc::LongNumber x("19602");
    abc::LongNumber y("99");
    std::cout << x / y << std::endl;
}