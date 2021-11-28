#pragma once

#ifndef Plant_H
#define Plant_H

#include "Creature.h"


class Plant: public Creature
{
public:	
	//Plant(std::vector <Creature* >* creatures, bool random_parameters = true);
	Plant(bool random_parameters = true);

	virtual std::pair <Creature::RESULT_OF_ACTION, Creature*> action() override;
	virtual Creature* eating(Creature* creature_food) override;
	virtual Creature* mooving() override;
	virtual Creature* reproduction(Creature* creature) override;
	virtual bool can_reproduce() override;
	virtual void die() override;
};

#endif //!1