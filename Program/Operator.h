#pragma once
#include <iostream>
#include "Struct.h"
#include "Function.h"

BigInt operator+(BigInt num1, BigInt num2);
BigInt operator-(BigInt num1, BigInt num2);
BigInt operator*(BigInt num1, BigInt num2);
BigInt operator/(BigInt num1, BigInt num2);
BigInt operator/(const BigInt number, const int divisor);
BigInt operator%(BigInt a, BigInt b);

BigInt operator~(BigInt number);
BigInt operator&(BigInt& num1, BigInt& num2);
BigInt operator|(BigInt& num1, BigInt& num2);
BigInt operator^(BigInt& num1, BigInt& num2);

BigInt operator>>(BigInt& number, int move);
BigInt operator<<(BigInt& number, int move);
