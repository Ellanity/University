#include "WorldDirector.h"


int main()
{
	std::ios::sync_with_stdio(false);
	srand((unsigned int)time(0));

	WorldDirector world_director;
	World* world = world_director.create_new_world();

	world->set_sizes(std::make_pair((int)20, (int)60));
	world->generate_creatures();
	
	world->print_step();
	std::string a;
	while (std::getline(std::cin, a))
	{
		world->generate_step();
		world->print_step();
	}

	//World* world_from_file = world_director.create_new_world("world_from_file.txt");
	
	world_director.delete_world(world);
	return 0;
}