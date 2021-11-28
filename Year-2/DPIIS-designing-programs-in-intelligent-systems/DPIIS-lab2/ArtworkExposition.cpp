#include "ArtworkExposition.h"


void ArtworkExposition::show_exposition()
{
	std::cout << ArtworkPicture::_description << "\n";
	std::cout << ArtworkSculpture::get_author() << "\n";
	std::cout << _age << "\n";
}
