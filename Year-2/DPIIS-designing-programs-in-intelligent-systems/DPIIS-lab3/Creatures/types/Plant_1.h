#pragma once

#ifndef Plant_1_H
#define Plant_1_H

#include "../Plant.h"


class Plant_1: public Plant
{
public:	
	Plant_1(bool random_parameters = true);

	virtual Creature* reproduction(Creature* creature) override;
	virtual bool _interface() override;
};

#endif //!1