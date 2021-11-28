#pragma once

#ifndef Predator_H
#define Predator_H

#include "Creature.h"
#include "../World.h"

class World;
class Predator : public Creature
{
private:
	World* world;
public:
	Predator(World* world, bool random_parameters = true);

	virtual std::pair <Creature::RESULT_OF_ACTION, Creature*> action() override;
	virtual Creature* eating(Creature* creature_food) override;
	virtual Creature* mooving() override;
	virtual Creature* reproduction(Creature* creature) override;
	virtual bool can_reproduce() override;
	virtual void die() override;
};

#endif //!1