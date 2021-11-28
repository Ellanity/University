#pragma once

#ifndef World_H
#define World_H

#include "Creatures/Creature.h"
#include "Creatures/Plant.h"
#include "Creatures/Herbivore.h"
#include "Creatures/Predator.h"


class World
{
protected:
	std::string prev_picture;

	std::pair <int, int> world_sizes;
	//std::vector < std::pair<int, int> > occupied_positions;	
	std::vector <Creature*> creatures;
	
	bool sizes_determined;
	bool creatures_generated;
	
	int count_of_steps;

	bool locate_creature_on_map(Creature* creature);
	std::pair <int, int> generate_random_position_for_creature();

	class WorldMap {
	public:
		class WorldMapCell {
		public:
			//std::pair <int, int> coordinates;
			std::vector <Creature*> creatures;
		};
		std::pair <int, int> world_sizes;
		std::vector < std::vector <WorldMapCell> > map;
		bool check_creature_with_same_type_in_cell(std::pair <int, int > position,Creature* creature);
		bool check_exist_position(std::pair <int, int> position);
	};
	WorldMap world_map;
public:
	std::string world_name;
	int world_id;

	World(int world_id, std::string world_name = "");

	void generate_step();
	void print_step();
	 
	void set_sizes(std::pair <int, int> sizes);
	void generate_creatures();
	void delete_creature(Creature* creature);

	// Getters
	std::pair <int, int> get_world_size() { return this->world_sizes; };
	std::vector <Creature*>* get_creatures() { return &(this->creatures); };
	int get_count_of_steps() { return this->count_of_steps; };
	WorldMap* get_world_map() { return &(this->world_map); };

	//std::vector < std::pair<int, int> >* get_occupied_positions() { return &(this->occupied_positions); };
	//void add_position_to_occupied(std::pair <int, int> position) { this->occupied_positions.push_back(position); };


	~World();
};

#endif //!1
