#pragma once

#ifndef ArtworkPublic_H
#define ArtworkPublic_H


#include "Artwork.h"
class ArtworkPublic :
    public Artwork
{
    //ArtworkPublic() : Artwork::Artwork() { class_id = 5; };
public:
    ArtworkPublic(
        int age = DEFAULT_AGE, std::string author = DEFAULT_AUTHOR, std::string description = DEFAULT_DESCRIPTION
    ) : Artwork::Artwork(age, author, description) {
        class_id = 5;
    };

    virtual void installation() { std::cout << "ArtworkPublic"; };
};


#endif // !1
