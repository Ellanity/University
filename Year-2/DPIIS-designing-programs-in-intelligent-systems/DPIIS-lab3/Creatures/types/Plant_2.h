#pragma once

#ifndef Plant_2_H
#define Plant_2_H

#include "../Creature.h"
#include "../Plant.h"

//class Plant;
//class Creature;
class Plant_2 : public Plant
{
public:
	Plant_2(bool random_parameters = true);
	virtual Creature* reproduction(Creature* creature) override;
	virtual bool _interface() override;
};

#endif //!1