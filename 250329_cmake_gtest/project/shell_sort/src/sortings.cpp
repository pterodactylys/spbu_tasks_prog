#include "sortings.hpp"

void tools::sortings::shell_sort_default(int* const arr, const int size) {
    int current_range = 1;
    while (3 * current_range + 1 <= (size + 2) / 3)
        current_range = 3 * current_range + 1;
    for (; current_range > 0; current_range /= 3) {
        for( int i = current_range; i < size; ++i) {
        int temp = arr[i];
        int j = i;
        for (; j >= current_range && arr[j - current_range] > temp; j -= current_range )
            arr[j] = arr[j - current_range];
        arr[j] = temp ;
        }
    }
}