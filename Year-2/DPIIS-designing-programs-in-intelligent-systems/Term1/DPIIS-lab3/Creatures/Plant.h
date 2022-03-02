#pragma once

#ifndef Plant_H
#define Plant_H

#include "Creature.h"


class Plant: public Creature
{
public:	
	Plant(bool random_parameters = true);

	virtual std::pair <Creature::RESULT_OF_ACTION, Creature*> action() override;
	virtual Creature* eating(Creature* creature_food) override;
	virtual Creature* mooving() override;
	virtual bool can_reproduce() override;
	virtual bool _interface() = 0;
};

#include "types/Plant_1.h"
#include "types/Plant_2.h"

#endif //!1