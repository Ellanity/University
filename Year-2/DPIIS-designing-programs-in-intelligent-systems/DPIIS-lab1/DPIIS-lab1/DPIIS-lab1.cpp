// DPIIS-lab1.cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "long_arithmetic.h"


int main(int argc, char* argv[])
{
    std::string num;
    std::cin >> num;
    BigInt a(num);
    std::cout << a << "\n";
    return 0;
}
