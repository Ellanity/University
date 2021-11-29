#include "Plant.h"


Plant::Plant(bool random_parameters)
{
	symbol_on_map = char(176);
	type_id = 10;
	
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

std::pair <Creature::RESULT_OF_ACTION, Creature*>Plant::action()
{
	bool action_has_been_performed = false;
	if (health_points < 100 && !action_has_been_performed)
	{
		health_points += 20;
		if (health_points > 100)
			health_points = 100;
		action_has_been_performed = true;
	}

	std::pair <Creature::RESULT_OF_ACTION, Creature*> result;

	short int num_of_action = rand() % 6;
	switch (num_of_action)
	{
	case 0:
		result = std::make_pair(Creature::RESULT_OF_ACTION::REPRODUCTION, this->reproduction(nullptr));
		break;
	default:
		result = std::make_pair(Creature::RESULT_OF_ACTION::NO, nullptr);
		break;
	}
	return result;
}

Creature* Plant::eating(Creature* creature_food)
{
	return nullptr;
}

Creature* Plant::mooving()
{
	return nullptr;
}

/*Creature* Plant::reproduction(Creature* creature)
{
	this->health_points = 60;
	Plant* plant = new Plant();
	plant->position = this->position;
	plant->health_points = rand() % 80;
	return plant;
}*/

bool Plant::can_reproduce()
{
	return true;
}
