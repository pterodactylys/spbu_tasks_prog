#pragma once

#include <cstddef>
		
namespace abc {
	template <typename T> 
	class Vector {
		private:
			static constexpr std::size_t START_CAPACITY = 10;

			T* arr = nullptr;
			std::size_t capacity = START_CAPACITY;
			std::size_t size = 0;

		public:
			Vector();
			Vector(const Vector&);
			Vector& operator = (const Vector& other);
			~Vector();
			
			std::size_t get_size() const noexcept;
			std::size_t get_capacity() const noexcept;
			bool has_item(const T& value) const noexcept;
			bool insert(const std::size_t position, const T& value);
			void print() const noexcept;
			void push_back(const T& value);
			bool remove_first(const T& value);
	};
}
