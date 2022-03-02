#pragma once

#ifndef ArtworkProtected_H
#define ArtworkProtected_H


#include "Artwork.h"
class ArtworkProtected :
    protected Artwork
{
    //ArtworkProtected() : Artwork::Artwork() { class_id = 6; };
    virtual void installation() { std::cout << "ArtworkProtected"; };
public:
    ArtworkProtected(
        int age = DEFAULT_AGE, std::string author = DEFAULT_AUTHOR, std::string description = DEFAULT_DESCRIPTION
    ) : Artwork::Artwork(age, author, description) {
        class_id = 6;
    };

    int transmitter() { return get_class_id(); };
};


#endif // !1