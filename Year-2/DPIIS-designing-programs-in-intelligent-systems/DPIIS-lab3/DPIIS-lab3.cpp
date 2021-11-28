#include "WorldDirector.h"


int main()
{
	std::ios::sync_with_stdio(false);

	srand(time(0));
	WorldDirector world_director;
	World* world = world_director.create_new_world();
	// 20 40
	world->set_sizes(std::make_pair((int)20, (int)60));
	world->generate_creatures();
	
	//for (int i = 0; i < 20; i++) {
	
	world->print_step();
	std::string a;
	while (std::getline(std::cin, a))
	{
		//system("cls");
		//std::cout << "new step \n";
		world->generate_step();
		world->print_step();
		//std::cout << "step is ready \n";
	}

	//World* world_from_file = world_director.create_new_world("world_from_file.txt");
	
	world_director.delete_world(world);
	return 0;
}