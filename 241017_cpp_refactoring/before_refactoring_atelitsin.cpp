#include <iostream>

int main(){
	const int arr_size = 10;
    int arr[arr_size];
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << "введите " << i << " элемент" << std::endl;
        std::cin >> arr[i];
    }
	
    bool is_increasing = true;
    for (int i = 0; i < arr_size; i++) {
		if (arr[i] > arr[i + 1]) {
            is_increasing = false;
			break;
		}
    }
	
    if (is_increasing == true) {
        std::cout << "последовательность возрастающая" << std::endl;
    }
	else {
		std::cout << "последовательность не возрастающая" << std::endl;
	}

    return 0;
}
