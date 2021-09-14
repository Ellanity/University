#pragma once
#ifndef long_arithmetic_H
#define long_arithmetic_H

#include <vector>
#include <string>
#include <sstream>  /* streamstring */
#include <iomanip>  /* setw */


class BigInt {
private:
	/* Basis size of the cell in numver */
	static const int cell = 1e9;

	/* Number itself */
	std::vector<int> _digits;

	/* Sign (+/-) */
	bool _is_negative;

	/**/
	void _remove_leading_zeros();
	void _shift_right();

	class _divide_by_zero : public std::exception {};

public:
	/* Constructors */
	BigInt();
	BigInt(std::string str);
	BigInt(signed long long l);
	BigInt(unsigned long long l);

	/**/
	/* Conversion operator */
	/* Allows [explicitly/implicitly] cast an object to std::string. */
	const BigInt operator -() const;
	const BigInt operator +() const;
	operator std::string() const;

	/* The friendly function [friend] is not a member of the class, */
	/* But has access to private fields */
	friend std::ostream& operator << (std::ostream& os, const BigInt& bi);

	friend bool operator==(const BigInt& first, const BigInt& second);
	friend bool  operator<(const BigInt& first, const BigInt& second);
	friend bool operator!=(const BigInt& first, const BigInt& second);
	friend bool operator<=(const BigInt& first, const BigInt& second);
	friend bool  operator>(const BigInt& first, const BigInt& second);
	friend bool operator>=(const BigInt& first, const BigInt& second);
	friend bool operator==(const BigInt& first, signed long long second);
	friend bool  operator<(const BigInt& first, signed long long second);
	friend bool operator!=(const BigInt& first, signed long long second);
	friend bool operator<=(const BigInt& first, signed long long second);
	friend bool  operator>(const BigInt& first, signed long long second);
	friend bool operator>=(const BigInt& first, signed long long second);

	friend const BigInt operator+(const BigInt first, const BigInt& second);
	friend const BigInt operator-(const BigInt first, const BigInt& second);
	friend const BigInt operator*(const BigInt& first, const BigInt& second);
	friend const BigInt operator/(const BigInt& first, const BigInt& second);
	friend const BigInt operator%(const BigInt& first, const BigInt& second);
	friend const BigInt operator+(const BigInt first, signed long long second);
	friend const BigInt operator-(const BigInt first, signed long long second);
	friend const BigInt operator*(const BigInt& first, signed long long second);
	friend const BigInt operator/(const BigInt& first, signed long long second);
	friend const BigInt operator%(const BigInt& first, signed long long second);

	/* Operations are performed directly only on the object itself */
	BigInt& operator+=(const BigInt& value);
	BigInt& operator-=(const BigInt& value);
	BigInt& operator+=(const signed long long value);
	BigInt& operator-=(const signed long long value);

	const BigInt operator++();
	const BigInt operator--();
	const BigInt operator++(int);
	const BigInt operator--(int);
};

#endif // !1