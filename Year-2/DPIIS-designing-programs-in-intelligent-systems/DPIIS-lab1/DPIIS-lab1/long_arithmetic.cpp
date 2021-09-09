#include "long_arithmetic.h"

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


const BigInt BigInt::operator-() const
{
    BigInt copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

const BigInt BigInt::operator+() const
{
    return BigInt(*this);
}

BigInt::operator std::string() const
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}


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

    return false;
}

bool operator<(const BigInt& first, const BigInt& second)
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
            for (long long i = first._digits.size() - 1; i >= 0; --i)
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
