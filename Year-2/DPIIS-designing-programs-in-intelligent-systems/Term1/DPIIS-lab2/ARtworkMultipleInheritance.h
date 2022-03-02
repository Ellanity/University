#pragma once

#ifndef ARtworkMultipleInheritance_H
#define ARtworkMultipleInheritance_H

#include "ArtworkPublic.h"
#include "ArtworkProtected.h"
#include "ArtworkPrivate.h"

class ARtworkMultipleInheritance :
    public ArtworkPublic, public ArtworkProtected, public ArtworkPrivate
{
public:
    virtual void installation() override { std::cout << "ARtworkMultipleInheritance"; }
};

#endif // !1
