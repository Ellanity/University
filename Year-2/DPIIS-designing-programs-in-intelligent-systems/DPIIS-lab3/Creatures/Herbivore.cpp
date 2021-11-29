#include "Herbivore.h"


Herbivore::Herbivore(World* world, bool random_parameters)
{
	type_id = 20;
	this->world = world;

	symbol_on_map = char(177);
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

std::pair <Creature::RESULT_OF_ACTION, Creature*>Herbivore::action()
{
	short int num_of_action = 3;
	bool can_eat = false, have_partner_in_cell = false, _die = false;
	Creature *partner = nullptr , *creature_food = nullptr;
	for (int creature_index = 0; creature_index < (int)this->world->get_world_map()->map[this->position.first][this->position.second].creatures.size(); creature_index++) {
		if (this->world->get_world_map()->map[this->position.first][this->position.second].creatures[creature_index]->type_of_food == Creature::TYPE_OF_FOOD::NO &&
			this->world->get_world_map()->map[this->position.first][this->position.second].creatures[creature_index]->health_points > 0)
		{
			can_eat = true;
			creature_food = this->world->get_world_map()->map[this->position.first][this->position.second].creatures[creature_index];
		}
	}

	for (int creature_index = 0; creature_index < (int)this->world->get_world_map()->map[this->position.first][this->position.second].creatures.size(); creature_index++) {
		if (typeid(*this) == typeid(*(this->world->get_world_map()->map[this->position.first][this->position.second].creatures[creature_index])) &&
			this->world->get_world_map()->map[this->position.first][this->position.second].creatures[creature_index]->gender != this->gender &&
			this->world->get_world_map()->map[this->position.first][this->position.second].creatures[creature_index]->can_reproduce())
		{
			have_partner_in_cell = true;
			partner = this->world->get_world_map()->map[this->position.first][this->position.second].creatures[creature_index];
		}
	}
	
	if (count_of_steps_without_food > count_of_steps_can_live_without_food || health_points <= 0 || age > max_age + rand() % 5)
		_die = true;

	if (_die)
		num_of_action = 3;
	else if (have_partner_in_cell && this->can_reproduce())
		num_of_action = 0;
	else if (can_eat)
		num_of_action = 1;
	else
		num_of_action = 2;

	std::pair <Creature::RESULT_OF_ACTION, Creature*> result;

	switch (num_of_action)
	{
	case 0:
		result = std::make_pair(Creature::RESULT_OF_ACTION::REPRODUCTION, this->reproduction(partner));
		break;
	case 1:
		result = std::make_pair(Creature::RESULT_OF_ACTION::EATING, this->eating(creature_food));
		break;
	case 2:
		result = std::make_pair(Creature::RESULT_OF_ACTION::MOOVING, this); // this->mooving());
		break;
	case 3:
		result = std::make_pair(Creature::RESULT_OF_ACTION::DIE, this);
		break;
	default:
		result = std::make_pair(Creature::RESULT_OF_ACTION::NO, nullptr);
		break;
	}

	if (food_points <= 0)
		count_of_steps_without_food++;
	else
		count_of_steps_without_food = 0;

	food_points -= need_food_for_one_step;
	if (food_points < 0) food_points = 0;
	age++;
	return result;
}

Creature* Herbivore::eating(Creature* creature_food)
{
	if (creature_food->health_points > 0) {
		short int eated = (rand() % 100) + 10;
		if (creature_food->health_points > eated) {
			this->food_points += eated;
			this->_size += eated / 30;
			creature_food->health_points -= eated;
		}
		else {
			this->food_points += creature_food->health_points;
			this->_size += (creature_food->health_points) / 10;
			creature_food->health_points = 0;
		}
	}
	return creature_food;
}

Creature* Herbivore::mooving()
{
	bool no_food = false, instinct_of_reproduction = false, danger = false;
	if (food_points < 50)
		no_food = true;

	std::vector <std::pair<int, int >>danger_positions;

	/*for (int i = this->position.first - distance_it_can_overcome; i <= this->position.first + 2; i++) {
		for (int j = this->position.second - distance_it_can_overcome; j <= this->position.second + 2; j++){
			if (this->world->get_world_map()->check_exist_position(std::make_pair(i, j))){
				for (int creature_index = 0; creature_index < this->world->get_world_map()->map[i][j].creatures.size(); creature_index++) {
					if (this->world->get_world_map()->map[i][j].creatures[creature_index]->type_of_food == Creature::TYPE_OF_FOOD::MEAT)
					{
						danger = true;
						danger_positions.push_back(std::make_pair(i, j));
					}
				}
			}
		}
	}*/

	if (!no_food && !danger)
		instinct_of_reproduction = true;

	int dist_now = (int)1e9, index_now = -1;
	std::pair <int, int> begin_position, end_position, position_to_relocate = this->position;
	begin_position = this->position;

	int x1 = this->position.first, y1 = this->position.second;
	
	if (danger) {
		int safty_kf = (int)1e9;
		for (int i = this->position.first - distance_it_can_overcome; i <= this->position.first + 2; i++) {
			for (int j = this->position.second - distance_it_can_overcome; j <= this->position.second + 2; j++) {
				if (this->world->get_world_map()->check_exist_position(std::make_pair(i, j))) {
					int safty_kf_now = 0;
					for (int k = 0; k < (int)danger_positions.size(); k++) {
						int x2 = danger_positions[k].first,
							y2 = danger_positions[k].second;
						safty_kf += (int)(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
					}
					if (safty_kf_now < safty_kf)
					{
						safty_kf = safty_kf_now;
						int x2 = i,
							y2 = j;
						int dist = (int)(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
						position_to_relocate = std::make_pair(i, j);
						if (dist < distance_it_can_overcome)
							this->position = position_to_relocate;
						else
						{
							double k = dist / this->distance_it_can_overcome;
							int x = abs(position_to_relocate.first - this->position.first),
								y = abs(position_to_relocate.second - this->position.second);

							int xn = int(x / k);
							int yn = int(y / k);

							if (position_to_relocate.first < this->position.first)
								this->position.first -= xn;
							else
								this->position.first += xn;

							if (position_to_relocate.second < this->position.second)
								this->position.second -= yn;
							else
								this->position.second += yn;
						}
					}
				}
			}
		}
	}
	else {
		for (int creature_index = 0; creature_index < (int)this->world->get_creatures()->size(); creature_index++) {
			if (
				(no_food && this->world->get_creatures()->at(creature_index)->type_of_food == Creature::TYPE_OF_FOOD::NO &&
					this->world->get_creatures()->at(creature_index)->health_points > 0)
				||
				(instinct_of_reproduction &&
					((typeid(*(this->world->get_creatures()->at(creature_index))) == typeid(*(this))) &&
						(this->world->get_creatures()->at(creature_index)->gender != this->gender) &&
						(this->world->get_creatures()->at(creature_index)->can_reproduce()))
					)
				)
			{
				int x2 = this->world->get_creatures()->at(creature_index)->position.first, y2 = this->world->get_creatures()->at(creature_index)->position.second;
				int dist = (int)(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
				if (dist < dist_now)
				{
					dist_now = dist; index_now = creature_index;
					position_to_relocate = this->world->get_creatures()->at(creature_index)->position;
				}
			}

		}
		if (index_now != -1) {

			if (dist_now < this->distance_it_can_overcome)
				this->position = position_to_relocate;
			else {
				double k = dist_now / this->distance_it_can_overcome;
				int x = abs(position_to_relocate.first - this->position.first),
					y = abs(position_to_relocate.second - this->position.second);

				int xn = int(x / k);
				int yn = int(y / k);

				if (position_to_relocate.first < this->position.first)
					this->position.first -= xn;
				else
					this->position.first += xn;

				if (position_to_relocate.second < this->position.second)
					this->position.second -= yn;
				else
					this->position.second += yn;
			}
		}
	}
	end_position = this->position;
	
	// changing position in map
	if (begin_position != end_position)
	{
		for (int i = 0; i < (int)this->world->get_world_map()->map[begin_position.first][begin_position.second].creatures.size(); i++)
			if (this->world->get_world_map()->map[begin_position.first][begin_position.second].creatures[i] == this)
			{
				this->world->get_world_map()->map[begin_position.first][begin_position.second].creatures.erase(this->world->get_world_map()->map[begin_position.first][begin_position.second].creatures.begin() + i);
				break;
			}
		this->world->get_world_map()->map[end_position.first][end_position.second].creatures.push_back(this);
	}

	return this;
}

/*
Creature* Herbivore::reproduction(Creature* creature)
{
	//std::cout << " reproduction ";
	this->_size -= 30;
	this->food_points -= 30;
	creature->_size -= 30;
	creature->food_points -= 30;
	
	Herbivore* herbivore = new Herbivore(this->world);
	
	herbivore->position = this->position;
	herbivore->_size = 100;
	herbivore->food_points = 150;
	
	return herbivore;
}
*/

/*bool Herbivore::can_reproduce()
{
	if (this->_size >= 70 && this->food_points >= 40 && age < 100 &&
		this->world->get_world_map()->map[this->position.first][this->position.second].creatures.size() < 4)
		return true;
	else
		return false;
}*/