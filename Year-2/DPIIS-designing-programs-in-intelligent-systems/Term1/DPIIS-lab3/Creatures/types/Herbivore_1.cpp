#include "Herbivore_1.h"


Herbivore_1::Herbivore_1(World* world, bool random_parameters)
{
	type_id = 21;
	symbol_on_map = char(177);
	this->world = world;

	if (random_parameters == true) {
		can_change_position = true;
		distance_it_can_overcome = 3;

		have_health_points = false;
		health_points = 1;

		need_food = true;
		type_of_food = Creature::TYPE_OF_FOOD::PLANT;
		food_points = 50;
		need_food_for_one_step = (_size / 10) + (rand() % 5) + 5;
		count_of_steps_without_food = 0;
		count_of_steps_can_live_without_food = 4;

		chance_to_survive_in_danger_situation = rand() % 40 + 10;

		have_size = true;
		_size = 90;

		have_life_span = true;
		age = 0;
		max_age = rand() % 100 + 50;

		can_reproduce_in_neighboring_cell = false;
		need_a_breeding_partner = true;
		have_gender = true;
		gender = rand() % 2;
	}
}

Creature* Herbivore_1::reproduction(Creature* creature)
{
	this->_size -= 30;
	this->food_points -= 30;
	creature->_size -= 30;
	creature->food_points -= 30;

	Herbivore_1* herbivore = new Herbivore_1(this->world);

	herbivore->position = this->position;
	herbivore->_size = 100;
	herbivore->food_points = 150;

	return herbivore;
}

bool Herbivore_1::can_reproduce()
{
	if (this->_size >= 70 && this->food_points >= 40 && 5 < age < 135 &&
		this->world->get_world_map()->map[this->position.first][this->position.second].creatures.size() < 4)
		return true;
	else
		return false;
}

bool Herbivore_1::_interface()
{
	return false;
}
