/*! This define in order not to receive warnings during compilation in the visual studio */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "long_arithmetic.h"

#define FS BIP.first, BIP.second
#define AB BigInt& A, BigInt& B

using std::cout;
using std::cin;

int menu();
int user_check();
std::pair<BigInt, BigInt> create_nums();
void sum(AB);
void increment_decrement_positive(AB);
void subtraction(AB);
void increment_decrement_negative(AB);
void assignment_sum(AB);
void assignment_subtraction(AB);
void comparsion(AB);
void less(AB);
void more(AB);
void less_or_equal(AB);
void more_or_equal(AB);
void multiply(AB);
void dividing(AB);
void remainder(AB);

/*! 
    \brief Small programm to check correct operation of the class 
    \author Eldar Poplauski Contacts: [eldarpoplauski111@gmail.com]
*/
int main(int argc, char* argv[])
{   
    int returned = 0;
    while (returned == 0)
    {
        returned = menu();
    }
    return 0;
}

int menu() {
    system("cls");
    cout << "Check operation: \n";
    cout << "1 ] + \n";
    cout << "2 ] ++ \n";
    cout << "3 ] - \n";
    cout << "4 ] -- \n";
    cout << "5 ] += \n";
    cout << "6 ] -= \n";
    cout << "7 ] == \n";
    cout << "8 ] < \n";
    cout << "9 ] > \n";
    cout << "10] <= \n";
    cout << "11] >= \n";
    cout << "12] * \n";
    cout << "13] / \n";
    cout << "14] % \n";
    cout << "15] Exit \n";
    cout << "[Enter number]: ";

    int n;
    cin >> n;
    std::pair <BigInt, BigInt> BIP;
    
    if (n < 15)
        BIP = create_nums();
    else
        return 1;

    switch (n)
    {
    case 1:
        sum(FS);
        break;
    case 2:
        increment_decrement_positive(FS);
        break;
    case 3:
        subtraction(FS);
        break;
    case 4:
        increment_decrement_negative(FS);
        break;
    case 5:
        assignment_sum(FS);
        break;
    case 6:
        assignment_subtraction(FS);
        break;
    case 7:
        comparsion(FS);
        break;
    case 8:
        less(FS);
        break;
    case 9:
        more(FS);
        break;
    case 10:
        less_or_equal(FS);
        break;
    case 11:
        more_or_equal(FS);
        break;
    case 12:
        multiply(FS);
        break;
    case 13:
        dividing(FS);
        break;
    case 14:
        remainder(FS);
        break;
    default:
        return 1;
    }

    return user_check();
}

int user_check()
{
    cout << "Is this this answer correct [y/n]?: ";
    char ans; cin.clear(); cin >> ans;
    return ans == 'y' ? 0 : 1;
}

std::pair<BigInt, BigInt> create_nums()
{
    std::string a, b;
    cin.clear();
    cout << "Enter first  num: \n";
    cin >> a;
    cin.clear();
    cout << "Enter second num: \n";
    cin >> b;
    BigInt A(a);
    BigInt B(b);
    return std::make_pair(A, B);
}

//1
void sum(AB) {
    cout << "sum: " << (A + B) << "\n";
}
//2
void increment_decrement_positive(AB) {
    ++A; B++;
    cout << "Increment[first num]: " << A << "\nDecrement[second num]: " << B << "\n";
}
//3
void subtraction(AB) {
    cout << "subtraction: " << (A - B) << "\n";
}
//4
void increment_decrement_negative(AB)
{
    --A; B--;
    cout << "Increment[first num]: " << A << "\nDecrement[second num]: " << B << "\n";
}
//5
void assignment_sum(AB) {
    A += B;
    cout << "[first += second]: " << A << "\n";
}
//6
void assignment_subtraction(AB) {
    A -= B;
    cout << "[first -= second]: " << A << "\n";
}
//7
void comparsion(AB) {
    cout << "[first == second]: " << (A == B) << "\n";
}
//8
void less(AB) {
    cout << "[first < second]: " << (A < B) << "\n";
}
//9
void more(AB) {
    cout << "[first > second]: " << (A > B) << "\n";
}
//10
void less_or_equal(AB) {
    cout << "[first < second]: " << (A <= B) << "\n";
}
//11
void more_or_equal(AB) {
    cout << "[first > second]: " << (A >= B) << "\n";
}
//12
void multiply(AB)
{
    cout << "[first * second]: " << (A * B) << "\n";
}
//13
void dividing(AB)
{
    cout << "[first / second]: " << (A / B) << "\n";
}
//14
void remainder(AB)
{
    cout << "[first % second]: " << (A % B) << "\n";
}
