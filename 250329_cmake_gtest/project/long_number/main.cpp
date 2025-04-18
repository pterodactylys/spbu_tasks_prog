#include "src/long_number.hpp"
#include <iostream>


int main() {
    const char* const str = "1120";
    const char* const str2 = "1000";
    abc::LongNumber a(str);
    abc::LongNumber b(str2);
    abc::LongNumber c(5784);
    std::cout << a / b << std::endl;
    std::cout << a % b << std::endl;
    std::cout << c << std::endl;
}
