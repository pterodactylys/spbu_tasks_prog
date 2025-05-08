#include "doubly_linked_list.hpp"

#include <iostream>

using abc::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() noexcept {
	begin = nullptr;
	end = nullptr;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other){
	if (other.begin == nullptr) {
		begin = nullptr;
		end = nullptr;
		return;
	}

	Node* current = other.begin;
	while (current != nullptr) {
		push_back(current->value);
		current = current->next;
	}
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (const DoublyLinkedList& other) {
	if (this == &other) {
		return *this;
	}
	for (Node* current = begin; current != nullptr; current = current->next) {
		delete current;
	}
	begin = nullptr;
	end = nullptr;
	Node* current = other.begin;
	while (current != nullptr) {
		push_back(current->value);
		current = current->next;
	}
	return *this;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	for (Node* current = begin; current != nullptr; ) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	begin = nullptr;
	end = nullptr;
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	std::size_t size = 0;
	for (Node* current = begin; current != nullptr; current = current->next) {
		size++;
	}
	return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	for (Node* current = begin; current != nullptr; current = current->next) {
		if (current->value == value) {
			return true;
		}
	}
	return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	for (Node* current = begin; current != nullptr; current = current->next) {
		std::cout << current->value << " ";
	}
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* new_node = new Node(value);
	if (begin == nullptr) {
		begin = new_node;
		end = new_node;
	} else {
		end->next = new_node;
		new_node->prev = end;
		end = new_node;
	}
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	if (begin == nullptr) {
		return false;
	}
	Node* current = begin;
	while (current != nullptr) {
		if (current->value == value) {
			if (current->prev != nullptr) {
				current->prev->next = current->next;
			} else {
				begin = current->next;
			}
			if (current->next != nullptr) {
				current->next->prev = current->prev;
			} else {
				end = current->prev;
			}
			delete current;
			return true;
		}
		current = current->next;
	}
	return false;
}

template class DoublyLinkedList<int>;
