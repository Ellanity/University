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

public:
    /* Constructors */
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

	friend bool operator ==(const BigInt& left, const BigInt& right);
	friend bool operator <(const BigInt& left, const BigInt& right);
	

	
}

#endif // !1