#include "WorldDirector.h"


std::string INPUT_FILE = "input.txt";


class Programm {
public:
	WorldDirector world_director;
	World* world;

	bool automatic;
	int sleep_time_between_frames;
	
	Programm(bool automatic = true, int sleep_time_between_frames = 10) {
		this->world = this->world_director.create_new_world();
		this->automatic = automatic;
		this->sleep_time_between_frames = sleep_time_between_frames;
	};
	
	void start() {
		system("cls");
		srand((unsigned int)time(0));
		//freopen(INPUT_FILE.c_str(), "r", stdin);
		
		//std::ios::sync_with_stdio(false);
		this->world->set_sizes(std::make_pair(20, 80));
		this->world->generate_creatures();

		bool _exit = false;
		if (this->automatic && !_exit)
		{
			do {
				this->world->generate_step();
				this->world->print_step();
				//Sleep(this->sleep_time_between_frames);
			} while (true && (this->world->count_of_herbivores + this->world->count_of_predators) != 0);
		}
		else {
			std::string str;
			while (std::getline(std::cin, str) && str != "exit");
			{
				this->world->generate_step();
				this->world->print_step();
			}
		}
		this->world_director.delete_world(this->world);
		world = nullptr;
	};

	~Programm() {
		delete world;
	}
};


int main(int argc, char* argv[])
{
	//std::ios::sync_with_stdio(false);
	Programm programm;
	programm.start();
	return 0;
}
