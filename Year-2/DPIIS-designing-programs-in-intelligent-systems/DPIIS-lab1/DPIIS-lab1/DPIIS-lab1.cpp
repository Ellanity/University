// DPIIS-lab1.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "long_arithmetic.h"


using std::cout;
using std::cin;

int main(int argc, char* argv[])
{
    std::string num;
    cin >> num;
    BigInt a(num);
    cin >> num;
    BigInt b = num;
    cout << "a: " << a << "\n" << "b: " << b << "\n";
    cout << "a == b: " << (a == b) << "\n";
    cout << "a - b: " << a - b << "\n";
    cout << "a + b: " << a + b << "\n";
    a++; b--; --b; ++a;
    cout << "a++ ++a: " << a << "\n" << "b-- --b: " << b << "\n";
    a -= 10; b += 10;
    cout << "a -= 10: " << a << "\n" << "b += 10: " << b << "\n";
    cout << "b + 10 == a - 10: " << ((b + 10) == (a - 10)) << "\n";
    cout << "\n\n" << "a: " << a << "\n" << "b: " << b << "\n";
    cout << "a * 1001: " << a * 1001 << "\n";
    cout << "a * b: " << a * b << "\n"; 
    cout << "a / 1000: " << a / 1000 << "\n";
    cout << "a / b: " << a / b << "\n"; 
    cout << "a % b: " << a % b << "\n"; 

    return 0;
}
