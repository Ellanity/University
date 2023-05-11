#pragma once

#ifndef WorldDirector_H
#define WorldDirector_H

#include "World.h"


class WorldDirector
{
protected:
	static int count_of_created_worlds;
public:
	std::vector <World*> worlds;
	
	WorldDirector();

	World* create_new_world();
	World* create_new_world(std::string file);
	void delete_world(World* world);

	~WorldDirector();
};

#endif //!1
