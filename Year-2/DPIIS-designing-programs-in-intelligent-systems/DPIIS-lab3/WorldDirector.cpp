#include "WorldDirector.h"


int WorldDirector::count_of_created_worlds = 0;

WorldDirector::WorldDirector()
{}

World* WorldDirector::create_new_world()
{
	//std::cout << "\x1b[31;1mCreating\x1b[0m a new \x1b[32;1mworld\x1b[0m!\n";
	//std::cout << "Creating a new world\n";
	this->count_of_created_worlds++;
	World* world = new World(this->count_of_created_worlds);
	world->world_id = this->count_of_created_worlds;
	this->worlds.push_back(world);
	return world;
}

World* WorldDirector::create_new_world(std::string file)
{
	return nullptr;
}

void WorldDirector::delete_world(World* world)
{
	for (int world_index = 0; world_index < this->worlds.size(); world_index++) {
		if ((world == this->worlds[world_index]) || (world->world_id == this->worlds[world_index]->world_id))
		{
			delete this->worlds[world_index];
			this->worlds[world_index] = NULL;
			this->worlds.erase(this->worlds.begin() + world_index);
			break;
		}
	}
}

WorldDirector::~WorldDirector()
{
	for (int world_index = 0; world_index < this->worlds.size(); world_index++) {
		delete this->worlds[world_index];
		this->worlds[world_index] = NULL;
	}
}
