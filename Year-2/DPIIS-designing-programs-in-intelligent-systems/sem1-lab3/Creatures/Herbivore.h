#pragma once

#ifndef Herbivore_H
#define Herbivore_H

#include "Creature.h"
#include "../World.h"


class World;
class Herbivore: public Creature
{
protected:
	World* world;
public:	
	Herbivore(World* world = nullptr, bool random_parameters = true);

	virtual std::pair <Creature::RESULT_OF_ACTION, Creature*> action() override;
	virtual Creature* eating(Creature* creature_food) override;
	virtual Creature* mooving() override;
	//virtual Creature* reproduction(Creature* creature) = 0;
	//virtual bool can_reproduce() = 0;
	virtual bool _interface() = 0;
};

#include "./types/Herbivore_1.h"
#include "./types/Herbivore_2.h"

#endif //!1