#pragma once

#ifndef Predator_2_H
#define Predator_2_H

#include "../Predator.h"


class World;
class Predator_2 : public Predator
{
public:
	Predator_2(World* world = nullptr, bool random_parameters = true);

	virtual Creature* reproduction(Creature* creature) override;
	virtual bool _interface() override;
	virtual bool Predator::can_reproduce() override;
};

#endif //!1