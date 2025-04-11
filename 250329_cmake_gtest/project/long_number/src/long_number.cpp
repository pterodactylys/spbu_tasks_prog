#include "long_number.hpp"

using abc::LongNumber;
		
LongNumber::LongNumber() {
	length = 1;
	sign = 1;
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(const char* const str) {
	int len = sizeof(str) / sizeof(str[0]);
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
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	length = 0;
	delete[] numbers;
	numbers = nullptr;
	sign = 0;
}

// LongNumber& LongNumber::operator = (const char* const str) {
// 	// TODO
// }

// LongNumber& LongNumber::operator = (const LongNumber& x) {
// 	// TODO
// }

// LongNumber& LongNumber::operator = (LongNumber&& x) {
// 	// TODO
// }

// bool LongNumber::operator == (const LongNumber& x) const {
// 	// TODO
// }

// bool LongNumber::operator != (const LongNumber& x) const {
// 	// TODO
// }

// bool LongNumber::operator > (const LongNumber& x) const {
// 	// TODO
// }

// bool LongNumber::operator < (const LongNumber& x) const {
// 	// TODO
// }

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
// int LongNumber::get_length(const char* const str) const noexcept {
// 	// TODO
// }

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
