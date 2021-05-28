#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstdio>
#include <sstream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>

#include "Operator.h"
#include "Struct.h"
#include "Function.h"
using namespace std;

int main(int argc, char** argv)
{
    using namespace std::chrono;
    const char* inp = argv[1];
    const char* out = argv[2];
    freopen(inp, "r", stdin);
    freopen(out, "w", stdout);
    string line, word;
    int base;
    bool checktime;
    if(argc == 4){  //neu muon xuat thoi gian thi them checktime
        checktime = true;
    }
    else{
        checktime = false;
    }
    while (getline(cin, line)) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        BigInt num,num1,num2;
        string push[10];
        int cnt = 0;
        stringstream ss(line);
        while (ss >> word) {
            push[cnt++] = word ;
        }
        base = stoi(push[0]);
        if (push[0] == "10" && push[1] == "2") {
            num.SetData(10,push[2]);
            cout << To_string(toBinary(num)) << endl;
        }
        else if (push[0] == "2" && push[1] == "10") {
            num.SetData(2, push[2]);
            cout << To_string(toDecimal(num)) << endl;
        }
        else if (push[1] == "~") {
            num.SetData(base, push[2]);
            cout << To_string(~num) << endl;
        }
        else {
            num1.SetData(base, push[1]);
            num2.SetData(base, push[3]);
            if (push[2] == "+")
                cout << To_string(num1 + num2) << endl;
            else if (push[2] == "-")
                cout << To_string(num1 - num2) << endl;
            else if (push[2] == "*")
                cout << To_string(num1 * num2) << endl;
            else if (push[2] == "%")
                cout << To_string(num1 % num2) << endl;
            else if (push[2] == ">>") {
                int move = stoi(push[3]);
                cout << To_string(num1 >> move) << endl;
            }
            else if (push[2] == "<<") {
                int move = stoi(push[3]);
                cout << To_string(num1 << move) << endl;
            }
            else if (push[2] == "&") {
               cout << To_string(num1 & num2) << endl;
            }
            else if (push[2] == "|") {
                cout << To_string(num1 | num2)<<endl;
            }
            else if (push[2] == "^") {
                cout << To_string(num1 ^ num2) << endl;
            }
        }
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1;

        if(checktime == true){
            cout << endl;
            cout << "It took " << time_span.count() << " milliseconds.";
            cout << endl << endl;
        }
        // check time
    }
    return 0;
}