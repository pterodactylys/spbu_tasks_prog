#include <gtest/gtest.h>
#include "../src/print.hpp"
#include "../src/sortings.hpp"

TEST(SortTest, Standart) {
    int arr[] = {3, 1, 4, 2};
    const int expected[] = {1, 2, 3, 4};
    tools::sortings::shell_sort_default(arr, 4);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}