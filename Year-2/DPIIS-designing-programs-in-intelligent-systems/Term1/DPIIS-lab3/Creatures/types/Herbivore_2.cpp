#include "Herbivore_2.h"


Herbivore_2::Herbivore_2(World* world, bool random_parameters)
{
	type_id = 22;
	symbol_on_map = char(177);
	this->world = world;

	if (random_parameters == true) {
		can_change_position = true;
		distance_it_can_overcome = 1;

		have_health_points = false;
		health_points = 1;

		need_food = true;
		type_of_food = Creature::TYPE_OF_FOOD::PLANT;
		food_points = 200;
		need_food_for_one_step = (_size / 8) + (rand() % 5) + 5;
		count_of_steps_without_food = 0;
		count_of_steps_can_live_without_food = 10;

		chance_to_survive_in_danger_situation = rand() % 40 + 10;

		have_size = true;
		_size = 300;

		have_life_span = true;
		age = 0;
		max_age = rand() % 100 + 100;

		can_reproduce_in_neighboring_cell = false;
		need_a_breeding_partner = true;
		have_gender = true;
		gender = rand() % 2;
	}
}

Creature* Herbivore_2::reproduction(Creature* creature)
{
	this->_size -= 100;
	this->food_points -= 100;
	creature->_size -= 100;
	creature->food_points -= 100;

	Herbivore_2* herbivore = new Herbivore_2(this->world);

	herbivore->position = this->position;
	herbivore->_size = 300;
	herbivore->food_points = 400;

	return herbivore;
}

bool Herbivore_2::can_reproduce()
{
	if (this->_size >= 150 && this->food_points >= 150 && 10 < age < 190 &&
		this->world->get_world_map()->map[this->position.first][this->position.second].creatures.size() < 4)
		return true;
	else
		return false;
}

bool Herbivore_2::_interface()
{
	return false;
}