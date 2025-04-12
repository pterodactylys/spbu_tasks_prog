class LongNumber:
    def __init__(self, value):
        if isinstance(value, int):
            self.value = [int(digit) for digit in str(value)]
        elif isinstance(value, str) and value.isdigit():
            self.value = [int(digit) for digit in value]
        elif isinstance(value, list) and all(isinstance(d, int) and 0 <= d <= 9 for d in value):
            self.value = value
        else:
            raise ValueError("Value must be a non-negative integer, a string of digits, or a list of digits.")

    def __add__(self, other):
        if not isinstance(other, LongNumber):
            raise TypeError("Operand must be a LongNumber.")
        result = []
        carry = 0
        self_digits = self.value[::-1]
        other_digits = other.value[::-1]
        max_len = max(len(self_digits), len(other_digits))

        for i in range(max_len):
            digit1 = self_digits[i] if i < len(self_digits) else 0
            digit2 = other_digits[i] if i < len(other_digits) else 0
            total = digit1 + digit2 + carry
            result.append(total % 10)
            carry = total // 10

        if carry:
            result.append(carry)

        return LongNumber(result[::-1])

    def __sub__(self, other):
        if not isinstance(other, LongNumber):
            raise TypeError("Operand must be a LongNumber.")
        if self < other:
            raise ValueError("Result of subtraction cannot be negative.")

        result = []
        borrow = 0
        self_digits = self.value[::-1]
        other_digits = other.value[::-1]

        for i in range(len(self_digits)):
            digit1 = self_digits[i]
            digit2 = other_digits[i] if i < len(other_digits) else 0
            diff = digit1 - digit2 - borrow
            if diff < 0:
                diff += 10
                borrow = 1
            else:
                borrow = 0
            result.append(diff)

        # Remove leading zeros
        while len(result) > 1 and result[-1] == 0:
            result.pop()

        return LongNumber(result[::-1])

    def __mul__(self, other):
        if not isinstance(other, LongNumber):
            raise TypeError("Operand must be a LongNumber.")
        result = [0] * (len(self.value) + len(other.value))

        for i in range(len(self.value) - 1, -1, -1):
            carry = 0
            for j in range(len(other.value) - 1, -1, -1):
                product = self.value[i] * other.value[j] + result[i + j + 1] + carry
                result[i + j + 1] = product % 10
                carry = product // 10
            result[i + j] += carry

        # Remove leading zeros
        while len(result) > 1 and result[0] == 0:
            result.pop(0)

        return LongNumber(result)

    def __truediv__(self, other):
        if not isinstance(other, LongNumber):
            raise TypeError("Operand must be a LongNumber.")
        if other == LongNumber(0):
            raise ZeroDivisionError("Division by zero is not allowed.")

        dividend = int("".join(map(str, self.value)))
        divisor = int("".join(map(str, other.value)))
        quotient = dividend // divisor

        return LongNumber([int(digit) for digit in str(quotient)])

    def __lt__(self, other):
        if len(self.value) != len(other.value):
            return len(self.value) < len(other.value)
        return self.value < other.value

    def __eq__(self, other):
        return self.value == other.value

    def __str__(self):
        return ''.join(map(str, self.value))

    def __repr__(self):
        return f"LongNumber({self.value})"
    
# Example usage of LongNumber class
if __name__ == "__main__":
    # Create LongNumber instances
    num1 = LongNumber(12345)
    num2 = LongNumber("678990")
    num3 = LongNumber([1, 2, 3, 4, 5])

    # Addition
    sum_result = num1 + num2
    print(f"{num1} + {num2} = {sum_result}")  # Output: 12345 + 67890 = 80235

    # Subtraction
    sub_result = num2 - num1
    print(f"{num2} - {num1} = {sub_result}")  # Output: 67890 - 12345 = 55545

    # Multiplication
    mul_result = num1 * num3
    print(f"{num1} * {num3} = {mul_result}")  # Output: 12345 * 12345 = 152399025

    # Division
    div_result = num2 / num1
    print(f"{num2} / {num1} = {div_result}")  # Output: 67890 / 12345 = 5

    # Comparison
    print(f"{num1} < {num2}: {num1 < num2}")  # Output: 12345 < 67890: True
    print(f"{num1} == {num3}: {num1 == num3}")  # Output: 12345 == 12345: True
    print(12345678901234567890 + 12345678901234567891)