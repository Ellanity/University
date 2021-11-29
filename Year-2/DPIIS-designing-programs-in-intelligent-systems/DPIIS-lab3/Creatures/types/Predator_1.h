#pragma once

#ifndef Predator_1_H
#define Predator_1_H

#include "../Predator.h"


class World;
class Predator_1 : public Predator
{
public:
	Predator_1(World* world = nullptr, bool random_parameters = true);

	virtual Creature* reproduction(Creature* creature) override;
	virtual bool _interface() override;
	virtual bool Predator::can_reproduce() override;
};

#endif //!1