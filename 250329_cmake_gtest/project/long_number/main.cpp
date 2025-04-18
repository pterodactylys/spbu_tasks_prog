#include "src/long_number.hpp"
#include <iostream>

using abc::LongNumber;

int main() {
    abc::LongNumber x("1234567890");
    std::cout << x << std::endl;
    std::cout << x << std::endl;
    std::cout << x.get_digits_number() << std::endl;
    std::cout << x.get_rank_number(3) << std::endl;
    std::cout << x.is_negative() << std::endl;
    return 0;
}
