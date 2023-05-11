#include "Predator_1.h"


Predator_1::Predator_1(World* world, bool random_parameters)
{
	type_id = 31;
	symbol_on_map = char(178);
	this->world = world;

	if (random_parameters == true) {
		can_change_position = true;
		distance_it_can_overcome = 2;

		have_health_points = false;
		health_points = 1;

		need_food = true;
		type_of_food = Creature::TYPE_OF_FOOD::MEAT;
		food_points = 100;
		need_food_for_one_step = (_size / 30) + (rand() % 5);
		count_of_steps_without_food = 0;
		count_of_steps_can_live_without_food = 15;

		chance_to_survive_in_danger_situation = rand() % 90 + 10;

		have_size = true;
		_size = 150;

		have_life_span = true;
		age = 0;
		max_age = rand() % 100 + 50;

		can_reproduce_in_neighboring_cell = false;
		need_a_breeding_partner = true;
		have_gender = true;
		gender = rand() % 2;
	}
}

Creature* Predator_1::reproduction(Creature* creature)
{
	this->_size -= 40;
	this->food_points -= 30;
	creature->_size -= 30;
	creature->food_points -= 30;

	Predator_1* predator = new Predator_1(this->world);

	predator->position = this->position;
	predator->_size = 150;
	predator->food_points = 300;

	return predator;
}

bool Predator_1::can_reproduce()
{
	if (this->_size >= 50 && this->food_points >= 50 &&
		this->world->get_world_map()->map[this->position.first][this->position.second].creatures.size() < 4)
		return true;
	else
		return false;
}

bool Predator_1::_interface()
{
	return false;
}
