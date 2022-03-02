#pragma once

#ifndef Artwork_H
#define Artwork_H

#include <iostream>
#include <string>


extern const int MAX_AGE;
extern const int DEFAULT_AGE;
extern const std::string DEFAULT_AUTHOR;
extern const std::string DEFAULT_DESCRIPTION;


class Artwork 
{
protected:
	static int _count_of_instances;
	int _age;
	std::string _author;
public:
	int class_id = 0;
	std::string _description;

	Artwork();
	Artwork(int age, std::string author, std::string _description);

	~Artwork();

	int get_class_id() { return class_id; }
	int get_age();
	std::string get_author();
	int get_count_of_instances();
	virtual void installation() = 0;
};

#endif // !1