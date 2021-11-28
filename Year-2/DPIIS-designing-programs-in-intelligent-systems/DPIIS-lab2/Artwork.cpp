#include "Artwork.h"

const int MAX_AGE = 5000;
const int DEFAULT_AGE = 0;
const std::string DEFAULT_AUTHOR = "Folk art";
const std::string DEFAULT_DESCRIPTION = "No description";


int Artwork::_count_of_instances = 0;

Artwork::Artwork()
{
	_age = DEFAULT_AGE;
	_author = DEFAULT_AUTHOR;
	_description = DEFAULT_DESCRIPTION;
	_count_of_instances++;
}

Artwork::Artwork(int age = DEFAULT_AGE, std::string author = DEFAULT_AUTHOR, std::string description = DEFAULT_DESCRIPTION)
	: _age(age), _author(author), _description(description)
{
	_count_of_instances++;
}

Artwork::~Artwork()
{
	_count_of_instances--;
}

int Artwork::get_age() 
{ 
	return _age; 
}

std::string Artwork::get_author() 
{ 
	return _author; 
}

int Artwork::get_count_of_instances()
{
	return _count_of_instances;
}

