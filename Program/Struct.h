#pragma once
#include<iostream>
using namespace std;

struct BigInt
{
    int sign, base;
    int numBit = 128;
    string data; 

    BigInt& operator=(const BigInt &number) {
        sign = number.sign;
        base = number.base;
        data = number.data;
        return *this;
    }
    void SetData(int numBase, string number) {
        data = number;
        base = numBase;
        sign = 1;
        if(base == 2 && number.size() >= numBit && number[0] == '1'){
            sign = -1;
        }
        if (base == 10 && number[0] == '-'){
            sign = -1;
            data.erase(0, 1);
        }
    }
};