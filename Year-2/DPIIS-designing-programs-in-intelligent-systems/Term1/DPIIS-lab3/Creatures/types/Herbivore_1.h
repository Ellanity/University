#pragma once

#ifndef Herbivore_1_H
#define Herbivore_1_H

#include "../Herbivore.h"


class World;
class Herbivore_1 : public Herbivore 
{
public:
	Herbivore_1(World* world = nullptr, bool random_parameters = true);

	virtual Creature* reproduction(Creature* creature) override;
	virtual bool _interface() override;
	virtual bool Herbivore::can_reproduce() override;
};

#endif //!1