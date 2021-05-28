#pragma once

int compare(BigInt a, BigInt b);
void deleteZero(BigInt& number);
void addZero(BigInt& num1, BigInt& num2);
BigInt toBinary(BigInt number);
BigInt toDecimal(BigInt number);

BigInt Abs(BigInt number);
BigInt Min(BigInt& num1, BigInt& num2);
BigInt Max(BigInt& num1, BigInt& num2);
BigInt Pow(BigInt num,BigInt pow);
long digits(BigInt num);
string To_string(BigInt num);
bool is_prime(BigInt num);
BigInt To_base(BigInt num, int base);