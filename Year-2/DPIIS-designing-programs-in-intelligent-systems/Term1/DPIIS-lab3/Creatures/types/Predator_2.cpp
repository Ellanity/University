#include "Predator_2.h"


Predator_2::Predator_2(World* world, bool random_parameters)
{
	type_id = 32;
	symbol_on_map = char(178);
	this->world = world;

	if (random_parameters == true) {
		can_change_position = true;
		distance_it_can_overcome = 2;

		have_health_points = false;
		health_points = 1;

		need_food = true;
		type_of_food = Creature::TYPE_OF_FOOD::MEAT;
		food_points = 200;
		need_food_for_one_step = (_size / 50) + (rand() % 5);
		count_of_steps_without_food = 0;
		count_of_steps_can_live_without_food = 15;

		chance_to_survive_in_danger_situation = rand() % 90 + 10;

		have_size = true;
		_size = 250;

		have_life_span = true;
		age = 0;
		max_age = rand() % 100 + 100;

		can_reproduce_in_neighboring_cell = false;
		need_a_breeding_partner = true;
		have_gender = true;
		gender = rand() % 2;
	}
}

Creature* Predator_2::reproduction(Creature* creature)
{
	this->_size -= 100;
	this->food_points -= 100;
	creature->_size -= 100;
	creature->food_points -= 100;

	Predator_2* predator = new Predator_2(this->world);

	predator->position = this->position;
	predator->_size = 300;
	predator->food_points = 300;

	return predator;
}

bool Predator_2::can_reproduce()
{
	if (this->_size >= 150 && this->food_points >= 150 && 5 < age < 195 &&
		this->world->get_world_map()->map[this->position.first][this->position.second].creatures.size() < 4)
		return true;
	else
		return false;
}

bool Predator_2::_interface()
{
	return false;
}
