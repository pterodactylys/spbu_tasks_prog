#include "src/long_number.hpp"
#include <iostream>


int main() {
    const char* const str = "123456";
    const char* const str2 = "-5";
    abc::LongNumber a(str);
    abc::LongNumber b(str2);
    abc::LongNumber c = a - b;
    std::cout << a << std::endl;
    a = a * b;
    std::cout << a << std::endl;
}
