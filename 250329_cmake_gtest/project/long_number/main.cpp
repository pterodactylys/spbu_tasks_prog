#include "src/long_number.hpp"
#include <iostream>

using abc::LongNumber;

int main() {
    std::cout << " 100 / 6 = " << (LongNumber("100") / LongNumber("6")) << std::endl;
    std::cout << "-100 / 6 = " << (LongNumber("-100") / LongNumber("6")) << std::endl;
    std::cout << " 100 / -6 = " << (LongNumber("100") / LongNumber("-6")) << std::endl;
    std::cout << "-100 / -6 = " << (LongNumber("-100") / LongNumber("-6")) << std::endl;
    
    std::cout << "-15689341 / 99 = " << (LongNumber("-15689341") / LongNumber("99")) << std::endl;
    std::cout << "5 / -3 = " << (LongNumber("5") / LongNumber("-3")) << std::endl;
    
    return 0;
}