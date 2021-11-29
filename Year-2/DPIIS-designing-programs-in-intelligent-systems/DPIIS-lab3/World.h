#pragma once

#ifndef World_H
#define World_H

// CREATURES
#include "Creatures/Creature.h"

#include "Creatures/Plant.h"
#include "Creatures/Herbivore.h"
#include "Creatures/Predator.h"


class World
{
protected:
	int count_of_steps;

	std::pair <int, int> world_sizes;
	std::vector <Creature*> creatures;
	
	bool sizes_determined;
	bool creatures_generated;
	
	std::string prev_picture;

	bool locate_creature_on_map(Creature* creature);
	std::pair <int, int> generate_random_position_for_creature();

	class WorldMap {
	public:
		class WorldMapCell {
		public:
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
		
	int count_of_plants, count_of_herbivores, count_of_predators;
	void counting_creatures();
	
	int get_count_of_steps() { return this->count_of_steps; };
	WorldMap* get_world_map() { return &(this->world_map); };

	~World();
};

#endif //!1
