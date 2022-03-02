#include "Plant_2.h"


Plant_2::Plant_2(bool random_parameters)
{
	symbol_on_map = char(176);
	type_id = 12;
	if (random_parameters == true) {
		can_change_position = false;
		distance_it_can_overcome = 0;

		have_health_points = true;
		health_points = rand() % 100;

		need_food = false;
		type_of_food = TYPE_OF_FOOD::NO;
		food_points = 0;
		need_food_for_one_step = 0;
		count_of_steps_without_food = 0;
		count_of_steps_can_live_without_food = 0;

		chance_to_survive_in_danger_situation = 100;

		have_size = false;
		_size = 0;

		have_life_span = false;

		can_reproduce_in_neighboring_cell = true;
		need_a_breeding_partner = false;
		have_gender = false;
		gender = 0;
	}
}

Creature* Plant_2::reproduction(Creature* creature)
{
	this->health_points = 80;
	Plant_2* plant = new Plant_2();
	plant->position = this->position;
	plant->health_points = rand() % 60;
	return plant;
}

bool Plant_2::_interface()
{
	return false;
}
