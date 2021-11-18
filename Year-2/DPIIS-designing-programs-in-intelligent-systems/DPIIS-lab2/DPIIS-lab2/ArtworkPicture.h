#pragma once

#ifndef ArtworkPicture_H
#define ArtworkPicture_H

#include "Artwork.h"
#include <vector>


extern const std::vector <std::string> DEFAULT_PICTURE;
extern const int DEFAULT_SQUARE;


class ArtworkPicture : public Artwork
{
private:
    std::vector <std::string> _picture_array;
    int _square;
public:
    /*ArtworkPicture() : Artwork::Artwork() {
        this->set_picture(DEFAULT_PICTURE);
        _square = DEFAULT_SQUARE;
    };*/

    /*ArtworkPicture(
        int age = DEFAULT_AGE, std::string author = DEFAULT_AUTHOR, std::string description = DEFAULT_DESCRIPTION
    ) : Artwork::Artwork(age, author, description) {
        this->set_picture(DEFAULT_PICTURE);
        _square = DEFAULT_SQUARE;
    };*/

    ArtworkPicture(
        int age = DEFAULT_AGE, std::string author = DEFAULT_AUTHOR, std::string description = DEFAULT_DESCRIPTION,
        int square = DEFAULT_SQUARE, std::vector <std::string> picture_array = DEFAULT_PICTURE
    ) : Artwork::Artwork() {
        this->set_picture(picture_array);
        _square = square;
    };

    void installation() override;

    void set_picture(std::vector <std::string> picture_array);
    void print_picture();
    
    void set_square(int square) { _square = square; };
    int  get_square() { return _square; };
};

#endif // !1