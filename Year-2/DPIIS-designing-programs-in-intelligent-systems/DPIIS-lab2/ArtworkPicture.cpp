#include "ArtworkPicture.h"


const std::vector <std::string> DEFAULT_PICTURE(3, "###");
const int DEFAULT_SQUARE = 999;


void ArtworkPicture::installation()
{
	std::cout << "The painting is hung in the museum with pictures";
}

void ArtworkPicture::set_picture(std::vector<std::string> picture_array)
{
	_picture_array.clear();
	for (int i = 0; i < (int)picture_array.size(); i++)
		_picture_array.push_back(picture_array[i]);
}

void ArtworkPicture::print_picture()
{
	for (int i = 0; i < (int)_picture_array.size(); i++)
		std::cout << _picture_array[i] << "\n";
}
/*
ArtworkPicture::ArtworkPicture(
	int age, std::string author, std::string description,
	int square, std::vector <std::string> picture_array
)
{
	_age = age;
	_author = author;
	_description = description;
	_square = square;
	this->set_picture(picture_array);
};*/