#include "src/long_number.hpp"
#include <iostream>


int main() {
    const char* const str = "12345678901234567890";
    const char* const str2 = "12345678901234567891";
    abc::LongNumber a(str);
    abc::LongNumber b(str2);
    abc::LongNumber c = a;
    if (a > b) {
        std::cout << a << " > " << b << std::endl;
    } else if (a < b) {
        std::cout << a << " < " << b << std::endl;
    } else {
        std::cout << a << " == " << b << std::endl;
    }
}
