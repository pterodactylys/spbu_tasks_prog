#include "vector.hpp"

#include <iostream>

using abc::Vector;

template<typename T>
Vector<T>::Vector() {
	size = 0;
	capacity = START_CAPACITY;
	arr = new T[capacity];
	std::cout << "Construct" << std::endl;
}

template<typename T>
Vector<T>::~Vector() {
	if (arr != nullptr) {
		delete[] arr;
		arr = nullptr;
	}
	capacity = 0;
	size = 0;
	std::cout << "Destrust" << std::endl;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	return false;
}

template<typename T>
void Vector<T>::print() const noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if (size == capacity) {
		capacity *= 2;
		T* new_arr = new T[capacity];
		for (std::size_t i = 0; i < size; ++i) {
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
	}
	arr[size] = value;
	size++;
	std::cout << "Push back: " << value << std::endl;
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	for (std::size_t i = 0; i < size; ++i) {
		if (arr[i] == value) {
			for (std::size_t j = i; j < size - 1; ++j) {
				arr[j] = arr[j + 1];
			}
			size--;
			return true;
		}
	}
	return false;
}

template class Vector<int>;
