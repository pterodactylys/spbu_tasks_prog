#include <iostream>

int main() {
    const int arr_size = 5;
    int arr[arr_size] = {3, 6, 5, 9, 10};
    int arr_max = arr[0];
    int arr_min = arr[0];

    for (int i = 0; i < arr_size; i++) {
        if (arr[i] > arr_max) {
            arr_max = arr[i];
        }
        if (arr[i] < arr_min) {
            arr_min = arr[i];
        }
    }
    
    const float diff = double(arr_max) / double(arr_min);
    std::cout << diff << std::endl;
}