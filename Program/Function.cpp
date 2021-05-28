#include<string>
#include "Struct.h"
#include "Operator.h"
#include "Function.h"

int compare(BigInt a, BigInt b)//a > b = 1 | a < b = -1 | a == b = 0
{
    if (a.sign != b.sign) return (a.sign > b.sign) ? 1 : -1;
    if (a.data.length() != b.data.length())
    {
        if(a.sign > 0)
            return (a.data.length() > b.data.length()) ? 1 : -1;
        else 
            return (a.data.length() < b.data.length()) ? 1 : -1;
    }
    // if two lengths are the same
    for (int i = 0; i < a.data.length(); i++)
    {
        if (a.data[i] > b.data[i]) return (a.sign > 0) ? 1 : -1;
        if (a.data[i] < b.data[i]) return (a.sign > 0) ? -1 : 1;
    }
    return 0;
}
void deleteZero(BigInt &number) {
    reverse(number.data.begin(), number.data.end());
    while (number.data.size() > 0 && number.data.back() == '0') {
        number.data.pop_back();
    }
    reverse(number.data.begin(), number.data.end());
}
void addZero(BigInt& num1, BigInt& num2) {
    while (num1.data.length() < num2.data.length())
        num1.data = "0" + num1.data;
    while (num2.data.length() < num1.data.length())
        num2.data = "0" + num2.data;
    return;
}
BigInt toBinary(BigInt number)
{
    BigInt res, One;
    One.SetData(2, "1");
    res.sign = number.sign;
    res.base = 2;
    while (number.data != "0")
    {
        int lastdigit = number.data.back() - '0';
        res.data += char(lastdigit % 2 + '0');
        number = number / 2;
    }
    reverse(res.data.begin(), res.data.end());
    if (res.sign == -1) {
        for (int i = 0; i < res.data.size(); i++) {
            res.data[i] = (res.data[i] == '0') ? '1' : '0';
        }
        while(res.data.size() < res.numBit){
            res.data = "1" + res.data;
        }
        for(int i = res.data.size() - 1; i >= 0; i--){
            if(res.data[i] == '0'){
                res.data[i] = '1';
                break;
            }
            else{
                res.data[i] = '0';
            }
        }
    }
    return res;
}
BigInt toDecimal(BigInt number)
{
    BigInt two, Pow2, res, One;
    One.SetData(10, "1");
    res.base = 10;
    res.sign = number.sign;
    int Sign = res.sign;
    if (res.sign == -1) {
        number = ~number;
        number = number + One;
    }
    two.SetData(10,"2");
    Pow2.SetData(10,"1");
    for (int i = number.data.size() - 1; i >= 0; i--)
    {
        if (number.data[i] == '1')
        {
            res = res + Pow2;
        }
        Pow2 = Pow2 * two;
    }
    res.sign = Sign; 
    return res;
}

BigInt Abs(BigInt number) {
    if(number.sign == 1) return number;
    if(number.base == 10){
        number.sign = 1;
        return number;
    }
    else if(number.base == 2){
        BigInt dec = toDecimal(number);
        dec.sign = 1;
        number = toBinary(dec);
        number.sign = 1;
        return number;
    }
}
BigInt Min(BigInt& num1, BigInt& num2) {
    if (compare(num1, num2) == 1)
        return num2;
    return num1;
}
BigInt Max(BigInt& num1, BigInt& num2) {
    if (compare(num1, num2) == 1)
        return num1;
    return num2;
}
BigInt To_base(BigInt num, int base){
    BigInt res, BASE;
    BASE.SetData(10, to_string(base));
    res.sign = num.sign;
    num.sign = 1;
    while(num.sign > 0){
        string tmp = (num % BASE).data;
        reverse(tmp.begin(), tmp.end());
        res.data +=  tmp + ' ';
        num = num / BASE;
    }
    reverse(res.data.begin(), res.data.end());
    if(res.sign == -1){
        res.data[0] = '-';
    }else{
        res.data.erase(0, 1);
    }
    return res;
}

BigInt Pow(BigInt num, BigInt p) {
    BigInt One, res;
    One.SetData(num.base, "1");
    if(p.data == "0"){
        return One;
    }
    if(p.data.size() >= 7){
        res.data = "So lon qua, tui em khong tinh ra a :<<";
        return res;
    }
    res.base = num.base;
    if (res.base == 2) 
    {
        num = toDecimal(num);
        p = toDecimal(p);
    }
    BigInt tmp;
    tmp.SetData(10, "1");
    int IntP = stoi(p.data);
    for (int i = 0; i < IntP; i++) {
        tmp = tmp * num;
    }
    res.data = tmp.data;
    if(res.base == 2){
        res = toBinary(res);
    }
    return res;
}
long digits(BigInt num) {
    BigInt res;
    if (num.base == 2) {
        res = toDecimal(num); 
    }
    else res.data = num.data;
    return res.data.size();
}

string To_string(BigInt num) {
    if (num.base == 10 && num.sign == -1){
        return '-' + num.data;
    }
    return num.data;
}

bool is_prime(BigInt num) {
    if(num.base == 2){
        num.data = toDecimal(num).data;
    }
    int Int = stoi(num.data);
    if(num.data.size() >= 7){
        for (int i = 2; i * i <= 1000000; i++) {
            if (Int % i == 0) {
                return false;
            }
        }
        return true;
    }
    for(int i = 2; i*i <= Int; i++){
        if(Int%i == 0){
            return false;
        }
    }
    return true;
}
