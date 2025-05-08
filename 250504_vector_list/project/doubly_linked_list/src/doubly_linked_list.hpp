#pragma once

#include <cstddef>

namespace abc {
	template <typename T> 
	class DoublyLinkedList {
		private:
			class Node {
				public:
					T value;
					Node* prev = nullptr;
					Node* next = nullptr;
					
					Node(const T& value) : value(value) {}
						
					Node(const Node&) = delete;
					Node& operator = (const Node&) = delete;
			};

			Node* begin = nullptr;
			Node* end = nullptr;

		public:
			DoublyLinkedList() noexcept;
			DoublyLinkedList(const DoublyLinkedList& other);
			DoublyLinkedList& operator = (const DoublyLinkedList& other);
			~DoublyLinkedList();
			
			std::size_t get_size() const noexcept;
			bool has_item(const T& value) const noexcept;
			void print() const noexcept;
			void push_back(const T& value);
			bool remove_first(const T& value) noexcept;
	};
}