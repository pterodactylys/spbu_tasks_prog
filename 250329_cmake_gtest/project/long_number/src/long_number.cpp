#include "long_number.hpp"

using abc::LongNumber;
		
LongNumber::LongNumber() {
	length = 1;
	sign = 1;
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(const char* const str) {
	int len = get_length(str);
	if (len == 0) {
		length = 1;
		sign = 1;
		numbers = new int[length];
		numbers[0] = 0;
	}
	else {
		if (str[0] == '-') {
			sign = -1;
			len--;
		}
		else {
			sign = 1;
		}
		length = len;
		numbers = new int[length];
		int start = (str[0] == '-') ? 1 : 0;
		for (int i = start; i < len + start; i++) {
			numbers[i - start] = str[i] - '0';
		}
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	numbers = x.numbers;
	x.length = 0;
	x.sign = 0;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	length = 0;
	delete[] numbers;
	numbers = nullptr;
	sign = 0;
}

LongNumber& LongNumber::operator = (const char* const str) {
	int len = get_length(str);
	if (len == 0) {
		length = 1;
		sign = 1;
		numbers = new int[length];
		numbers[0] = 0;
	}
	else {
		if (str[0] == '-') {
			sign = -1;
			len--;
		}
		else {
			sign = 1;
		}
		length = len;
		delete[] numbers;
		numbers = new int[length];
		int start = (str[0] == '-') ? 1 : 0;
		for (int i = start; i < len + start; i++) {
			numbers[i - start] = str[i] - '0';
		}
	}
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this != &x) {
		length = x.length;
		sign = x.sign;
		delete[] numbers;
		numbers = new int[length];
		for (int i = 0; i < length; i++) {
			numbers[i] = x.numbers[i];
		}
	}
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (this != &x) {
		length = x.length;
		sign = x.sign;
		delete[] numbers;
		numbers = x.numbers;
		x.length = 0;
		x.sign = 0;
		x.numbers = nullptr;
	}
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (this == &x) {
		return true;
	}
	if (length != x.length || sign != x.sign) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			return false;
		}
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (this == &x) {
		return false;
	}
	if (sign != x.sign) {
		return sign > x.sign;
	}
	if (length != x.length) {
		if (sign == 1) {
			return length > x.length;
		}
		else {
			return length < x.length;
		}
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			if (sign == 1) {
				return numbers[i] > x.numbers[i];
			}
			else {
				return numbers[i] < x.numbers[i];
			}
		}
	}
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	if (this == &x) {
		return false;
	}
	if (sign != x.sign) {
		return sign < x.sign;
	}
	if (length != x.length) {
		if (sign == 1) {
			return length < x.length;
		}
		else {
			return length > x.length;
		}
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			if (sign == 1) {
				return numbers[i] < x.numbers[i];
			}
			else {
				return numbers[i] > x.numbers[i];
			}
		}
	}
	return false;
}

// LongNumber LongNumber::operator + (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator - (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator * (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator / (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator % (const LongNumber& x) const {
// 	// TODO
// }

// int LongNumber::get_digits_number() const noexcept {
// 	// TODO
// }

// int LongNumber::get_rank_number(int rank) const {
// 	// TODO
// }

// bool LongNumber::is_negative() const noexcept {
// 	// TODO
// }

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int count = 0;
	while (str[count] != '\0') {
		count++;
	}
	return count;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace abc {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.numbers == nullptr) {
			os << "0";
		}
		else {
			if (x.sign == -1) {
				os << "-";
			}
			for (int i = 0; i < x.length; i++) {
				os << x.numbers[i];
			}
		}
		return os;
	}
}
