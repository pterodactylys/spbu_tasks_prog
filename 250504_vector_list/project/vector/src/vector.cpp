#include "vector.hpp"

#include <iostream>

using abc::Vector;

template<typename T>
Vector<T>::Vector() {
	size = 0;
	capacity = START_CAPACITY;
	arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
	if (arr != nullptr) {
		delete[] arr;
		arr = nullptr;
	}
	capacity = 0;
	size = 0;
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
	capacity = other.capacity;
	size = other.size;
	arr = new T[capacity];
	for (std::size_t i = 0; i < size; ++i) {
		arr[i] = other.arr[i];
	}
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this != &other) {
		if (arr != nullptr) {
			delete[] arr;
		}
		capacity = other.capacity;
		size = other.size;
		arr = new T[capacity];
		for (std::size_t i = 0; i < size; ++i) {
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
std::size_t Vector<T>::get_capacity() const noexcept {
	return capacity;
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
	if (position > size) {
		return false;
	}
	if (size == capacity) {
		capacity *= 2;
		T* new_arr = new T[capacity];
		for (std::size_t i = 0; i < size; ++i) {
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
	}
	for (std::size_t i = size; i > position; --i) {
		arr[i] = arr[i - 1];
	}
	arr[position] = value;
	size++;
	return true;
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
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
    if (size == 0) return false;

    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            for (std::size_t j = i; j < size - 1; ++j) {
                arr[j] = arr[j + 1];
            }
            size--;

            if (capacity > 2 * size && capacity > START_CAPACITY) {
                capacity /= 2;
                T* new_arr = new T[capacity];
                for (std::size_t k = 0; k < size; ++k) {
                    new_arr[k] = arr[k];
                }
                delete[] arr;
                arr = new_arr;
            }
            return true;
        }
    }
    
    return false;
}

template class Vector<int>;
