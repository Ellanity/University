#pragma once

#ifndef Creature_H
#define Creature_H

// FOR ALGORITHMS
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <set>

// FOR PICTURE
#include <stdio.h>
#include <sstream>
#include <windows.h>


class Creature
{
public:
	int type_id = 0;

	char symbol_on_map;

	std::pair <int, int> position;
	bool can_change_position;
	short int distance_it_can_overcome;
	
	bool have_health_points;
	short int health_points;

	
	bool need_food;
	enum class TYPE_OF_FOOD { NO, ALL, PLANT, MEAT };
	TYPE_OF_FOOD type_of_food;
	short int food_points;
	short int need_food_for_one_step;
	short int count_of_steps_without_food;
	short int count_of_steps_can_live_without_food;

	short int chance_to_survive_in_danger_situation;

	bool have_size;
	short int _size;

	bool have_life_span;
	int age;
	int max_age;

	bool can_reproduce_in_neighboring_cell;
	bool need_a_breeding_partner;
	bool have_gender;
	short int gender;

	enum class RESULT_OF_ACTION { REPRODUCTION, EATING, MOOVING, DIE, NO };
	virtual std::pair <RESULT_OF_ACTION, Creature*> action() = 0;

	virtual Creature* eating  (Creature* creature_food) = 0;
	virtual Creature* mooving () = 0;
	virtual Creature* reproduction(Creature* creature) = 0;
	virtual bool can_reproduce() = 0;
	virtual bool _interface() = 0;
};

#endif //!1