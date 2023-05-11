#include "long_arithmetic.h"

/*! Procedure for removing leading zeros */
void BigInt::_remove_leading_zeros()
{
    while (this->_digits.size() > 1 &&
           this->_digits.back() == 0) {
        this->_digits.pop_back();
    }
    
    /* Zero cannot be negative */
    if (this->_digits.size() == 1 &&
        this->_digits[0] == 0) {
        this->_is_negative = false;
    }
}

/*! Åhe function of "shifting" the number to the right,
    which allows you to iterate over the digits sequentially */
void BigInt::_shift_right() {
    if (this->_digits.size() == 0)
    {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    /* Here the size of the array is at least two and the search goes to the penultimate digit*/
    for (size_t i = this->_digits.size() - 2; i > 0; i--) {
        this->_digits[i] = this->_digits[i - 1];
    }
    this->_digits[0] = 0;
}

/*! The standard constructor does nothing*/
BigInt::BigInt(){}

/*! \brief A constructor that fills a vector inside an object with standart integer type of values 
    \param[in] str - string consisting of digits and a postfix plus/minus sign
*/
BigInt::BigInt(std::string str)
{
    /* If string is emty, then number is zero */
    if (str.length() == 0) {    
        this->_is_negative = false;
    }
    else 
    {
        if (str[0] == '-') 
        {
            str = str.substr(1);  /* Get substring[indexes 1...n].Only number, no sign */
            this->_is_negative = true;
        }
        else {
            this->_is_negative = false;
        }

        /* Make vector of ints from string */
        for (long long i = str.length(); i > 0; i -= 9) 
        {
            if (i < 9) {
                this->_digits.push_back(atoi(str.substr(0, i).c_str()));
            }
            else {
                this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
            }
        }

        /* Remove leading zeros if exist*/
        this->_remove_leading_zeros();
    }
}

/*! \brief A constructor that fills a vector inside an object with standart integer type of values 
    \param[in] num - the number that the vector consists of (it can be either positive/negative)
*/
BigInt::BigInt(signed long long num)
{
    if (num < 0) 
    { 
        this->_is_negative = true; 
        num = -num; 
    }
    else 
        this->_is_negative = false;

    /* Make vector of ints from number */
    do 
    {
        this->_digits.push_back(num % BigInt::cell);
        num /= BigInt::cell;
    } while (num != 0);
}

/*! \brief A constructor that fills a vector inside an object with standart integer type of values
    \param[in] num - the number that the vector consists of (only positive)
*/
BigInt::BigInt(unsigned long long num)
{
    this->_is_negative = false;
    /* Make vector of ints from num */
    do
    {
        this->_digits.push_back(num % BigInt::cell);
        num /= BigInt::cell;
    } while (num != 0);
}

//! Changing the sign of a number to a positive one
const BigInt BigInt::operator+() const
{
    return BigInt(*this);
}

//! Changing the sign of a number to a negative one
const BigInt BigInt::operator-() const
{
    BigInt copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

//! Print a number to a stream and convert it to a string
BigInt::operator std::string() const
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

//! Output of a number
std::ostream& operator<<(std::ostream& out, const BigInt& bi)
{
    if (bi._digits.empty()) {
        out << 0;
    }
    else 
    {
        if (bi._is_negative) {
            out << '-';
        }
        out << bi._digits.back();
        
        char old_fill = out.fill('0');  /* Saving the current placeholder character */
        
        /* Print the following numbers in groups of 9 digits */
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) {
            out << std::setw(9) << bi._digits[i];
        }

        out.fill(old_fill);  /* Restoring old placeholder character */
    }

    return out;
}


bool operator==(const BigInt& first, const BigInt& second)
{
    /* Numbers of different characters are not exactly equal */
    if (first._is_negative != second._is_negative) {
        return false; 
    }

    /* Have two representations of zero [0/empty] -> need to handle this in particular */
    if (first._digits.empty() || 
       (first._digits.size() == 1 && first._digits[0] == 0))
    {
        if (second._digits.empty() || 
           (second._digits.size() == 1 && second._digits[0] == 0)) {
            return true;
        }
        else {
            return false;
        }
    }

    if (second._digits.empty() ||
       (second._digits.size() == 1 && second._digits[0] == 0))
    {
        if (first._digits.empty() ||
           (first._digits.size() == 1 && first._digits[0] == 0)) {
            return true;
        }
        else {
            return false;
        }
    }

    /* Do not have leading zeros -> the numbers must have the same number of digits */
    if (first._digits.size() != second._digits.size()) {
        return false;
    }
    
    /* Just compare each digit in numbers */
    for (size_t i = 0; i < first._digits.size(); i++) 
    {
        if (first._digits[i] != second._digits[i]) {
            return false;
        }
    }

    return true;
}

bool  operator<(const BigInt& first, const BigInt& second)
{
    if (first == second) 
    {
        return false;
    }

    if (first._is_negative)
    {
        if (second._is_negative) {
            return ((-second) < (-first));
        }
        else {
            return true;
        }
    }
    else if (second._is_negative)
    {
        return false;
    }
    else 
    {
        if (first._digits.size() != second._digits.size()) {
            return (first._digits.size() < second._digits.size());
        }
        else 
        {
            for (long long i = first._digits.size() - 1; i >= 0; i--)
            {
                if (first._digits[i] != second._digits[i]) {
                    return (first._digits[i] < second._digits[i]);
                }
            }
            return false;
        }
    }

    return false;
}

bool operator!=(const BigInt& first, const BigInt& second)
{
    return !(first == second);
}

bool operator<=(const BigInt& first, const BigInt& second)
{
    return (first < second || first == second);;
}

bool  operator>(const BigInt& first, const BigInt& second)
{
    return !(first <= second);
}

bool operator>=(const BigInt& first, const BigInt& second)
{
    return !(first < second);
}


bool operator==(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first == a);
}

bool  operator<(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first < a);
}

bool operator!=(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first != a);
}

bool operator<=(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first <= a);
}

bool  operator>(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first > a);
}

bool operator>=(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first >= a);
}


const BigInt operator+(BigInt first, const BigInt& second) {
    /* Here is ONLY THE ADDITION of two positive numbers
    the rest is written by changing the sign and subtracting */
    if (first._is_negative)
    {
        if (second._is_negative) {
            return -(-first + (-second));
        }
        else {
            return second - (-first);
        }
    }
    else if (second._is_negative) {
        return first - (-second);
    }
    int carry = 0;  /* Flag for transferring from the previous category */
    for (size_t i = 0; i < std::max(first._digits.size(), second._digits.size()) || carry != 0; i++)
    {
        if (i == first._digits.size()) {
            first._digits.push_back(0);
        }
        first._digits[i] += carry + (i < second._digits.size() ? second._digits[i] : 0);
        carry = first._digits[i] >= BigInt::cell;
        if (carry != 0) {
            first._digits[i] -= BigInt::cell;
        }
    }

    return first;
}

const BigInt operator-(BigInt first, const BigInt& second) {
    
    /* The same, only subtracting */
    if (second._is_negative) {
        return first + (-second);
    }
    else if (first._is_negative) {
        return -(-first + second);
    }
    /* Reverse if second bigger then first */
    else if (first < second) {
        return -(second - first);
    }
    
    int carry = 0;
    for (size_t i = 0; i < second._digits.size() || carry != 0; i++)
    {
        first._digits[i] -= carry + (i < second._digits.size() ? second._digits[i] : 0);
        carry = first._digits[i] < 0;
        if (carry != 0) {
            first._digits[i] += BigInt::cell;
        }
    }

    first._remove_leading_zeros();
    return first;
}

const BigInt operator*(const BigInt& first, const BigInt& second)
{
    BigInt result;
    result._digits.resize(first._digits.size() + second._digits.size());
    for (size_t i = 0; i < first._digits.size(); i++)
    {
        int carry = 0;
        long long cur;
        for (size_t j = 0; j < second._digits.size() || carry != 0; j++) 
        {
            cur = result._digits[i + j] +
                first._digits[i] * 1LL * (j < second._digits.size() ? second._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % BigInt::cell);
            carry = static_cast<int>(cur / BigInt::cell);
        }
    }

    result._is_negative = first._is_negative != second._is_negative;
    result._remove_leading_zeros();
    return result;
}

/*! \brief The division is made by the corner. 

    Let's start dividing from the higher categories. We need to reduce 
    the current value of the divisible by the maximum possible number 
    of divisible. We will search for this maximum value using a binary
    search. 
*/
const BigInt operator/(const BigInt& first, const BigInt& second)
{
    if (second == 0) 
        throw BigInt::_divide_by_zero();
    BigInt b = second;
    b._is_negative = false;
    BigInt result, current;
    result._digits.resize(first._digits.size());
    for (long long i = static_cast<long long>(first._digits.size()) - 1; i >= 0; i--) {
        current._shift_right();
        current._digits[0] = first._digits[i];
        current._remove_leading_zeros();
        int x = 0, l = 0, r = BigInt::cell;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInt t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            }
            else 
                r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._is_negative = first._is_negative != second._is_negative;
    result._remove_leading_zeros();
    return result;
}

const BigInt operator%(const BigInt& first, const BigInt& second)
{
    BigInt result = first - (first / second) * second;
    if (result._is_negative) {
        result += second;
    }
    return result;
}

const BigInt operator+(const BigInt first, signed long long second)
{
    BigInt a(second);
    return (first + a);
}

const BigInt operator-(const BigInt first, signed long long second)
{
    BigInt a(second);
    return (first - a);
}

const BigInt operator*(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first * a);
}

const BigInt operator/(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first / a);
}

const BigInt operator%(const BigInt& first, signed long long second)
{
    BigInt a(second);
    return (first % a);
}


BigInt& BigInt::operator+=(const BigInt& value)
{
    return *this = (*this + value);
}

BigInt& BigInt::operator-=(const BigInt& value)
{
    return *this = (*this - value);
}

BigInt& BigInt::operator+=(const signed long long value)
{
    BigInt a(value);
    return *this = (*this + a);
}

BigInt& BigInt::operator-=(const signed long long value)
{
    BigInt a(value);
    return *this = (*this - a);
}


const BigInt BigInt::operator++() {
    BigInt a((unsigned long long)1);
    return (*this += a);
}

const BigInt BigInt::operator ++(int) {
    BigInt a((unsigned long long)1);
    *this += a;
    return *this - a;
}

const BigInt BigInt::operator --() {
    BigInt a((unsigned long long)1);
    return (*this -= a);
}

const BigInt BigInt::operator --(int) {
    BigInt a((unsigned long long)1);
    *this -= a;
    return *this + a;
}
