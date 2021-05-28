#include "Operator.h"
#include "Struct.h"

BigInt operator<<(BigInt &number, int move) {
    BigInt res;
    res.sign = number.sign;
    res.base = number.base;
    if(number.base == 10){
        number = toBinary(number);
    }
    res.data = number.data;
    while (move--) {
        res.data += '0';
    }
    if(res.base == 10){
        res.data = toDecimal(res).data;
    }
    return res;
}

BigInt operator>>(BigInt& number, int move) {
    BigInt res;
    res.sign = number.sign;
    res.base = number.base;
    if(number.base == 10){
        number = toBinary(number);
    }
    res.data = number.data;
    while (move-- && res.data.size() > 0) {
        res.data.pop_back();
    }
    if(res.base == 10){
        res.data = toDecimal(res).data;
    }
    return res;
}

BigInt operator&(BigInt &num1, BigInt &num2) {
    BigInt res;
    res.base = num1.base;
    if(num1.sign == -1 && num2.sign == -1){
        res.sign = -1;
    }else{
        res.sign = 1;
    }
    if(res.base == 10){
        num1 = toBinary(num1);
        num2 = toBinary(num2);
    }
    addZero(num1, num2);
    for (int i = 0; i < num1.data.size(); i++) {
        res.data += (num1.data[i] + num2.data[i] == '1' + '1') ? "1" : "0";
    }
    if(res.base == 10){
        res = toDecimal(res);
    }
    return res;
}
BigInt operator|(BigInt& num1, BigInt& num2) {
    BigInt res;
    res.base = num1.base;
    if(num1.sign == 1 && num2.sign == 1){
        res.sign = 1;
    }else{
        res.sign = -1;
    }
    if(res.base == 10){
        num1 = toBinary(num1);
        num2 = toBinary(num2);
    }
    addZero(num1, num2);
    for (int i = 0; i < num1.data.size(); i++) {
        res.data += (num1.data[i] + num2.data[i] == '0' + '0') ? "0" : "1";
    }
    if(res.base == 10){
        res = toDecimal(res);
    }
    return res;
}
BigInt operator^(BigInt& num1, BigInt& num2) {
    BigInt res;
    res.base = num1.base;
    if(num1.sign == 1 && num2.sign == 1){
        res.sign = 1;
    }else{
        res.sign = -1;
    }
    if(res.base == 10){
        num1 = toBinary(num1);
        num2 = toBinary(num2);
    }
    addZero(num1, num2);
    for (int i = 0; i < num1.data.size(); i++) {
        res.data += (num1.data[i] == num2.data[i]) ? "0" : "1";
    }
    if(res.base == 10){
        res = toDecimal(res);
    }
    return res;
}
BigInt operator~(BigInt number) {
    BigInt res;
    res.base = number.base;
    res.sign = number.sign * -1;
    if(res.base == 10){
        number = toBinary(number);
    }
    for (int i = 0; i < number.data.size(); i++) {
        res.data += (number.data[i] == '0') ? "1" : "0";
    }
    if(res.base == 10){
        res = toDecimal(res);
    }
    return res;
}

BigInt operator-(BigInt num1, BigInt num2)
{
    BigInt res;
    res.base = num1.base;
    res.sign = 1;
    if(res.base == 2){
        num1 = toDecimal(num1);
        num2 = toDecimal(num2);
    }
    if (num1.sign == -1 && num2.sign == -1) { // am - am -2-(-3) = 3 - 2
        num1.sign = num2.sign = 1;
        swap(num1, num2);
    }

    if (num1.sign == -1 && num2.sign == 1) { // am - duong -2-3 = - (2+3)
        num1.sign = 1;
        res = num1 + num2;
        res.sign = -1;
        return res;
    }
    if (num1.sign == 1 && num2.sign == -1) { // duong - am 2-(-3) = 2 + 3
        num2.sign = 1;
        return num1 + num2;
    }
    addZero(num1, num2);
    if (compare(num1, num2) == -1)
    {
        swap(num1.data, num2.data);
        res.sign = -1;
    }
    int borrow = 0;
    for (int i = num1.data.length() - 1; i >= 0; i--)
    {
        int tmp = num1.data[i] - num2.data[i] - borrow;
        if (tmp < 0)
        {
            tmp += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        res.data = (char)(tmp % 10 + 48) + res.data;
    }
    while (res.data.length() > 1 && res.data[0] == '0')
        res.data.erase(0, 1);
    if(res.base == 2){
        res.data = toBinary(res).data;
    }
    return res;
}
BigInt operator/(const BigInt number, const int divisor)
{
    BigInt res;
    int Int = 0;
    for (int i = 0; i < number.data.size(); i++) {
        Int = Int * 10 + number.data[i] - '0';
        if (Int > divisor) {
            break;
        }
    }
    if (Int < divisor) {
        res.sign = 0;
        res.data = "0";
        return res;
    }
    res.sign = number.sign;
    int idx = 0;
    int temp = number.data[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number.data[++idx] - '0');
    while (number.data.size() > idx)
    {
        res.data += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + number.data[++idx] - '0';
    }
    return res;
}
BigInt operator+(BigInt num1, BigInt num2)
{
    BigInt res;
    res.base = num1.base;
    if(res.base == 2){
        num1 = toDecimal(num1);
        num2 = toDecimal(num2);
    }
    if (num1.sign == 1 && num2.sign == -1) { // duong + am
        num2.sign = 1;
        return num1 - num2;
    }
    if (num1.sign == -1 && num2.sign == 1) { // am + duong
        num1.sign = 1;
        return num2 - num1;
    }
    if (num1.sign == -1 && num2.sign == -1) //am + am
    {
        res.sign = -1;
    }
    else //duong + duong
    {
        res.sign = 1;
    }
    addZero(num1, num2);
    int carry = 0;
    for (int i = num1.data.length() - 1; i >= 0; i--)
    {
        int tmp = num1.data[i] - '0' + num2.data[i] - '0' + carry;
        carry = tmp / 10;
        tmp = tmp % 10;
        res.data = (char)(tmp + '0') + res.data;
    }
    if (carry > 0)
        res.data = "1" + res.data;
    if(res.base == 2){
        res = toBinary(res);
    }
    return res;
}
BigInt operator*(BigInt num1, BigInt num2)
{
    BigInt res;
    res.base = num1.base;
    res.sign = num1.sign * num2.sign;
    if(res.base == 2){
        num1 = toDecimal(num1);
        num2 = toDecimal(num2);
    }
    int n = num1.data.length();
    int m = num2.data.length();
    int len = n + m - 1;
    int carry = 0;
    for (int i = len; i >= 0; i--)
    {
        int tmp = 0;
        for (int j = n - 1; j >= 0; j--)
            if (i - j <= m && i - j >= 1)
            {
                tmp += (num1.data[j] - '0') * (num2.data[i - j - 1] - '0');
            }
        tmp += carry;
        carry = tmp / 10;
        res.data = (char)(tmp % 10 + 48) + res.data;
    }
    while (res.data.length() > 1 && res.data[0] == '0')
        res.data.erase(0, 1);
    if(res.base == 2){
        res = toBinary(res);
    }
    return res;
}

BigInt operator%(BigInt num1, BigInt num2) {
    BigInt res;
    res.base = num1.base;
    res.sign = num1.sign;
    num1.sign = num2.sign = 1;
    if(res.base == 2){
        num1.data = toDecimal(num1).data;
        num2.data = toDecimal(num2).data;
    }
    BigInt div = num1 / num2;
    res.data = (num1 - (div * num2)).data;
    if(res.base == 2){
        res.data = toBinary(res).data;
    }
    return res;
}

BigInt operator/(BigInt num1, BigInt num2)
{
    BigInt res;
    res.base = num1.base;
    if(num2.sign == 0){
        res.data =  "Loi chia cho 0 !!!";
        return res;
    }
    res.sign = num1.sign * num2.sign;
    if(res.base == 2){
        num1.data = toDecimal(num1).data;
        num2.data = toDecimal(num2).data;
    }
    num1.sign = 1;
    num2.sign = 1;
    if(compare(num1, num2) == -1){
        res.sign = 0;
        res.data = '0';
        return res;
    }
    BigInt tmp;
    tmp.base = 10;
    tmp.sign = 1;
    int i = 0;
    while(compare(tmp, num2) < 0 && i < num1.data.size()) {
        tmp.data += num1.data[i];
        i++;
    }
    while (i <= num1.data.size()){
        int div = 0;
        while((tmp - num2).sign == 1){
            tmp = tmp - num2;
            div++;
        }
        res.data += char(div + '0');
        tmp.data += num1.data[i];
        i++;
    }
    if(res.base == 2){
        res.data = toBinary(res).data;
    }
    return res;
}