#pragma once

#ifndef Herbivore_2_H
#define Herbivore_2_H

#include "../Herbivore.h"


class World;
class Herbivore_2 : public Herbivore
{
public:
	Herbivore_2(World* world = nullptr, bool random_parameters = true);

	virtual Creature* reproduction(Creature* creature) override;
	virtual bool _interface() override;
	virtual bool Herbivore::can_reproduce() override;
};

#endif //!1