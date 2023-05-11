#pragma once

#include <iostream>
#include <string>

class MyObject {
public:
	int main_value;
	std::string secondary_value;

	MyObject(int _main_value = 10, std::string _secondary_value = "this is not important value") {
		main_value = _main_value;
		secondary_value = _secondary_value;
	};

	friend bool operator< (const MyObject& obj1, const MyObject& obj2)
	{
		if (obj1.main_value < obj2.main_value)
			return true;
		else if (obj1.main_value == obj2.main_value)
			if (obj1.secondary_value < obj2.secondary_value)
				return true;
		return false;
	}

	friend bool operator== (const MyObject& obj1, const MyObject& obj2)
	{
		if (obj1.main_value == obj2.main_value &&
			obj1.secondary_value == obj2.secondary_value)
			return true;
		return false;
	};

	friend bool operator<= (const MyObject& obj1, const MyObject& obj2)
	{
		if (obj1 < obj2 || obj1 == obj2)
			return true;
		return false;
	};

	friend bool operator> (const MyObject& obj1, const MyObject& obj2)
	{
		if (!(obj1 < obj2) && !(obj1 == obj2))
			return true;
		return false;
	};
	
	friend bool operator>= (const MyObject& obj1, const MyObject& obj2)
	{
		if (obj1 > obj2 || obj1 == obj2)
			return true;
		return false;
	};

	MyObject& operator= (const MyObject& obj)
	{
		this->main_value = obj.main_value;
		this->secondary_value = obj.secondary_value;
		return *this;
	};

	friend std::ostream& operator<< (std::ostream& out, const MyObject& obj) {
		out << "[" << obj.main_value << ": " << obj.secondary_value << "]";
		return out;
	}
};