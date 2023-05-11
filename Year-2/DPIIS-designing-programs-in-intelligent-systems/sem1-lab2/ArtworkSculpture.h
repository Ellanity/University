#pragma once

#ifndef ArtworkSculpture_H
#define ArtworkSculpture_H

#include "Artwork.h"
#include <vector>


extern const int DEFAULT_VOLUME;


class ArtworkSculpture : public Artwork
{
private:
    int _volume;
public:
    ArtworkSculpture() : Artwork::Artwork() {
        _volume = DEFAULT_VOLUME;
    };

    ArtworkSculpture(
        int age, std::string author, std::string description
    ) : Artwork::Artwork(age, author, description) {
        _volume = DEFAULT_VOLUME;
    };

    void installation() override;

    void set_volume(int volume) { _volume = volume; };
    int  get_volume() { return _volume; };
};

#endif // !1