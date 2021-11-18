#pragma once

#include "ArtworkPicture.h"
#include "ArtworkSculpture.h"

#include <math.h>

#ifndef ArtworkExposition_H
#define ArtworkExposition_H

class ArtworkExposition : virtual public ArtworkPicture, virtual public ArtworkSculpture
{
private:
	int _age;
	std::string _author;
public:
	std::string _description;

	ArtworkExposition() : ArtworkPicture(), ArtworkSculpture() {
		_age = 0;
	};
	ArtworkExposition(
		int age, std::string author, std::string description
	) : ArtworkPicture(age, author, description),
		ArtworkSculpture(age, author, description) {
		_age = (int)std::min(ArtworkSculpture::_age, ArtworkPicture::_age);
	};

	void show_exposition();



	//override installation();
	/*
		
	*/
};

#endif // !1