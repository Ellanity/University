#pragma once

#ifndef ArtworkPrivate_H
#define ArtworkPrivate_H


#include "Artwork.h"
class ArtworkPrivate :
    private Artwork
{
    //ArtworkPrivate() : Artwork::Artwork() { class_id = 7; };
    virtual void installation() { std::cout << "ArtworkPrivate"; };
public:
    ArtworkPrivate(
        int age = DEFAULT_AGE, std::string author = DEFAULT_AUTHOR, std::string description = DEFAULT_DESCRIPTION
    ) : Artwork::Artwork(age, author, description) {
        class_id = 7;
    };

    int transmitter() { return get_class_id(); };
};

#endif // !1
