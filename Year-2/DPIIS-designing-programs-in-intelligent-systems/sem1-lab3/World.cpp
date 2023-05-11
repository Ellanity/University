#include "World.h"


// DEFINING ANSI CODE COLORS
//ESC[ 38;2;r;g;b m
//ESC[ 48;2;r;g;b m
#define COLOR_RED			"\x1b[31m"
#define COLOR_LIGHT_RED     "\x1b[31;1m"
#define COLOR_GREEN			"\x1b[32m"
#define COLOR_LIGHT_GREEN   "\x1b[32;1m"
#define COLOR_YELLOW		"\x1b[33m"
#define COLOR_LIGHT_YELLOW  "\x1b[37;1m"
#define COLOR_BLUE			"\x1b[34m"

#define COLOR_BLUE_LIGHT_ON_DARK		"\x1b[38;2;51;153;255m\x1b[48;2;0;0;153m"
#define COLOR_RED_BACKGROUND			"\x1b[48;2;241;76;76m"

#define COLOR_GREEN_BACKGROUND			"\x1b[48;2;0;204;102m"
#define COLOR_DARK_GREEN_BACKGROUND		"\x1b[48;2;67;169;87m"
#define COLOR_YELLOW_BACKGROUND			"\x1b[48;2;240;228;114m"
#define COLOR_DARK_YELLOW_BACKGROUND	"\x1b[48;2;208;180;45m"

#define COLOR_BROWN						"\x1b[38;2;170;120;70m"
#define COLOR_PURPLE_BACKGROUND			"\x1b[48;2;220;100;235m"

#define COLOR_BLACK		"\x1b[30m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"

#define COLOR_BRIGHT	"\x1b[1m"
#define COLOR_RESET		"\x1b[0m"

#define NOf Creature::TYPE_OF_FOOD::NO
#define MEATf Creature::TYPE_OF_FOOD::MEAT
#define PLANTf Creature::TYPE_OF_FOOD::PLANT

#define REPRODUCTION_ Creature::RESULT_OF_ACTION::REPRODUCTION
#define EATING_ Creature::RESULT_OF_ACTION::EATING
#define MOOVING_ Creature::RESULT_OF_ACTION::MOOVING
#define DIE_ Creature::RESULT_OF_ACTION::DIE
#define NO_ Creature::RESULT_OF_ACTION::NO


//WORLD
World::World(int world_id, std::string world_name)
{
	this->sizes_determined = false;
	this->creatures_generated = false;
	this->count_of_steps = 0;
	this->world_id = world_id;
	this->prev_picture = "";
}

void World::set_sizes(std::pair<int, int> sizes)
{
	if (this->sizes_determined == false) {
		this->world_sizes.first  = sizes.first;
		this->world_sizes.second = sizes.second;
		this->world_map.world_sizes.first  = sizes.first;
		this->world_map.world_sizes.second = sizes.second;
		this->sizes_determined = true;

		for (int i = 0; i < world_sizes.first; i++) {
			std::vector <WorldMap::WorldMapCell> empty_row;
			world_map.map.push_back(empty_row);
			for (int j = 0; j < world_sizes.second; j++) {
				WorldMap::WorldMapCell empty_cell;
				world_map.map[i].push_back(empty_cell);
			}
		}
	}
}

// WORLD INITIAL BALANCE
void World::generate_creatures()
{
	// Adjusting the formulas for the number of creatures will balance the game
	if (this->sizes_determined == true) {
		
		int cells_count = this->world_sizes.first * this->world_sizes.second;
		
		//PLANTS
		short int plants_count = cells_count / ((this->world_sizes.first + this->world_sizes.second) / 8);
		for (int plant_index = 0; plant_index < (int)(plants_count / 2); plant_index++) {
			Plant_1* plant = new Plant_1();
			plant->position = generate_random_position_for_creature();
			world_map.map[plant->position.first][plant->position.second].creatures.push_back(plant);
			this->creatures.push_back(plant);
		}
		for (int plant_index = 0; plant_index < (int)(plants_count / 2); plant_index++) {
			Plant_2* plant = new Plant_2();
			plant->position = generate_random_position_for_creature();
			world_map.map[plant->position.first][plant->position.second].creatures.push_back(plant);
			this->creatures.push_back(plant);
		}
		
		//HERBIVORES
		short int herbivores_count = cells_count / ((this->world_sizes.first + this->world_sizes.second) / 2);
		for (int herbivore_index = 0; herbivore_index < (int)(herbivores_count / 2); herbivore_index++) {
			Herbivore_1* herbivore = new Herbivore_1(this);
			herbivore->position = generate_random_position_for_creature();
			world_map.map[herbivore->position.first][herbivore->position.second].creatures.push_back(herbivore);
			this->creatures.push_back(herbivore);
		}
		for (int herbivore_index = 0; herbivore_index < (int)(herbivores_count / 2); herbivore_index++) {
			Herbivore_2* herbivore = new Herbivore_2(this);
			herbivore->position = generate_random_position_for_creature();
			world_map.map[herbivore->position.first][herbivore->position.second].creatures.push_back(herbivore);
			this->creatures.push_back(herbivore);
		}
		
		//PREDATORS
		short int predators_count = cells_count / ((this->world_sizes.first + this->world_sizes.second));
		for (int predator_index = 0; predator_index < (int)(predators_count / 2); predator_index++) {
			Predator_1* predator = new Predator_1(this);
			predator->position = generate_random_position_for_creature();
			world_map.map[predator->position.first][predator->position.second].creatures.push_back(predator);
			this->creatures.push_back(predator);
		}
		for (int predator_index = 0; predator_index < (int)(predators_count / 2); predator_index++) {
			Predator_2* predator = new Predator_2(this);
			predator->position = generate_random_position_for_creature();
			world_map.map[predator->position.first][predator->position.second].creatures.push_back(predator);
			this->creatures.push_back(predator);
		}
		this->creatures_generated = true;
		this->counting_creatures();
	}
}

void World::generate_step()
{
	if (this->sizes_determined == false) {
		std::cout << COLOR_RED << "ERROR: this world needs sizing" << COLOR_RESET;
		return;
	}
	if (this->creatures_generated == false) {
		std::cout << COLOR_RED << "ERROR: this world needs creatures" << COLOR_RESET;
		return;
	}

	int count_of_creatures_this_step = this->creatures.size();
	std::set <Creature*> died;
	
	for (int creature_index = 0; creature_index < count_of_creatures_this_step; creature_index++) 
	{
		std::pair <Creature::RESULT_OF_ACTION, Creature*> result = this->creatures[creature_index]->action();

		switch (result.first)
		{
		case Creature::RESULT_OF_ACTION::REPRODUCTION:
			locate_creature_on_map(result.second);
			break;
		case MOOVING_:
			this->creatures[creature_index]->mooving();
			break;
		case EATING_:
			this->creatures[creature_index]->eating(result.second);
			if (result.second->health_points <= 0)
				died.insert(result.second);
			break;
		case DIE_:
			died.insert(result.second);
			break;
		case NO_:
			break;
		default:
			break;
		}
	}

	
	for (auto it : died)
		this->delete_creature(it);

	this->counting_creatures();
	this->count_of_steps++;
}

void World::print_step()
{
	std::ostringstream out;
	if (this->sizes_determined == false) {
		std::cout << COLOR_RED << "ERROR: this world needs sizing" << COLOR_RESET;
		return;
	}
	if (this->creatures_generated == false) {
		std::cout << COLOR_RED << "ERROR: this world needs creatures" << COLOR_RESET;
		return;
	}	

	out << (char)201;
	for (int i = 0; i < this->world_sizes.second; i++)
		out << (char)205;
	out << (char)187 << "\n";

	for (int i = 0; i < this->world_sizes.first; i++) {
		out << (char)186;
		for (int j = 0; j < this->world_sizes.second; j++)
		{
			if (this->world_map.map[i][j].creatures.empty())
				out << (char)219;
			else
			{
				std::map <Creature::TYPE_OF_FOOD, bool> types_of_creatures_in_cell = {
					{NOf, false},
					{PLANTf, false},
					{MEATf, false}
				};

				for (int k = 0; k < (int)this->world_map.map[i][j].creatures.size(); k++) {
					if (this->world_map.map[i][j].creatures[k]->type_of_food == NOf)
						types_of_creatures_in_cell[NOf] = true;
					if (this->world_map.map[i][j].creatures[k]->type_of_food == PLANTf)
						types_of_creatures_in_cell[PLANTf] = true;
					if (this->world_map.map[i][j].creatures[k]->type_of_food == MEATf)
						types_of_creatures_in_cell[MEATf] = true;
				}

				if (types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
					out << (char)222;

				else if (types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
					out << (char)221 ;

				else if (types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
					out << (char)178 ;
				else if (!types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
					out << (char)222 ;

				else if (types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
					out << this->world_map.map[i][j].creatures[0]->symbol_on_map;
				else if (!types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
					out << this->world_map.map[i][j].creatures[0]->symbol_on_map;
				else if (!types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
					out << this->world_map.map[i][j].creatures[0]->symbol_on_map ;

			}
		}
		out << (char)186 << "\n";
	}

	out << (char)200;
	for (int i = 0; i < this->world_sizes.second; i++)
		out << (char)205 ;
	out << (char)188 << "\n";

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (prev_picture == "") {
		std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)201 << COLOR_RESET;
		for (int i = 0; i < this->world_sizes.second; i++) {
			std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)205 << COLOR_RESET;
		}
		std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)187 << COLOR_RESET << "\n";

		for (int i = 0; i < this->world_sizes.first; i++) {
			std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)186 << COLOR_RESET;
			for (int j = 0; j < this->world_sizes.second; j++)
			{
				if (this->world_map.map[i][j].creatures.empty())
					std::cout << COLOR_BROWN << (char)219 << COLOR_RESET;
				else
				{
					std::map <Creature::TYPE_OF_FOOD, bool> types_of_creatures_in_cell = {
						{NOf, false},
						{PLANTf, false},
						{MEATf, false}
					};

					for (int k = 0; k < (int)this->world_map.map[i][j].creatures.size(); k++) {
						if (this->world_map.map[i][j].creatures[k]->type_of_food == NOf)
							types_of_creatures_in_cell[NOf] = true;
						if (this->world_map.map[i][j].creatures[k]->type_of_food == PLANTf)
							types_of_creatures_in_cell[PLANTf] = true;
						if (this->world_map.map[i][j].creatures[k]->type_of_food == MEATf)
							types_of_creatures_in_cell[MEATf] = true;
					}

					if (types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_RED_BACKGROUND << COLOR_YELLOW << (char)222 << COLOR_RESET;
					else if (types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_YELLOW_BACKGROUND << COLOR_LIGHT_GREEN << (char)221 << COLOR_RESET;
					else if (types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_RED << (char)178 << COLOR_RESET;
					else if (!types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_YELLOW_BACKGROUND << COLOR_RED << (char)222 << COLOR_RESET;
					else if (types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf]) 
					{
						if (this->world_map.map[i][j].creatures[0]->type_id == 11)
							std::cout << COLOR_GREEN_BACKGROUND << COLOR_BLACK << this->world_map.map[i][j].creatures[0]->symbol_on_map << COLOR_RESET;
						else if (this->world_map.map[i][j].creatures[0]->type_id == 12)
							std::cout << COLOR_DARK_GREEN_BACKGROUND << COLOR_BLACK << this->world_map.map[i][j].creatures[0]->symbol_on_map << COLOR_RESET;
					}
					else if (!types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
					{
						if (this->world_map.map[i][j].creatures[0]->type_id == 21)
							std::cout << COLOR_YELLOW_BACKGROUND << COLOR_BLACK << this->world_map.map[i][j].creatures[0]->symbol_on_map << COLOR_RESET;
						else if (this->world_map.map[i][j].creatures[0]->type_id == 22)
							std::cout << COLOR_DARK_YELLOW_BACKGROUND << COLOR_BLACK << this->world_map.map[i][j].creatures[0]->symbol_on_map << COLOR_RESET;
					}
					else if (!types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
					{
						if (this->world_map.map[i][j].creatures[0]->type_id == 31)
							std::cout << COLOR_RED << this->world_map.map[i][j].creatures[0]->symbol_on_map << COLOR_RESET;
						else if (this->world_map.map[i][j].creatures[0]->type_id == 32)
							std::cout << COLOR_LIGHT_RED << this->world_map.map[i][j].creatures[0]->symbol_on_map << COLOR_RESET;
					}
				}
			}
			std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)186 << COLOR_RESET << "\n";
		}

		std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)200 << COLOR_RESET;
		for (int i = 0; i < this->world_sizes.second; i++) {
			std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)205 << COLOR_RESET;
		}
		std::cout << COLOR_BLUE_LIGHT_ON_DARK << (char)188 << COLOR_RESET << "\n";
	}
	else
	{
		for (int symbol_index = 0; symbol_index <= (int)out.str().size(); symbol_index++)
		{
			if (prev_picture[symbol_index] != out.str()[symbol_index])
			{
				short int x = (short int)(symbol_index % (this->world_sizes.second + 3)); // x_ y|
				short int y = (short int)(symbol_index / (this->world_sizes.second + 3)) - 1;
				if ((symbol_index / (this->world_sizes.first + 3)) != 0) y += 1;

				COORD symbol_position = { x, y };
				SetConsoleCursorPosition(h, symbol_position);

				int i = y - 1, j = x - 1;
				if (this->world_map.map[i][j].creatures.empty())
					std::cout << COLOR_BROWN << out.str()[symbol_index] << COLOR_RESET;
				else
				{
					std::map <Creature::TYPE_OF_FOOD, bool> types_of_creatures_in_cell = {
						{NOf, false},
						{PLANTf, false},
						{MEATf, false}
					};

					for (int k = 0; k < (int)this->world_map.map[i][j].creatures.size(); k++) {
						if (this->world_map.map[i][j].creatures[k]->type_of_food == NOf)
							types_of_creatures_in_cell[NOf] = true;
						if (this->world_map.map[i][j].creatures[k]->type_of_food == PLANTf)
							types_of_creatures_in_cell[PLANTf] = true;
						if (this->world_map.map[i][j].creatures[k]->type_of_food == MEATf)
							types_of_creatures_in_cell[MEATf] = true;
					}

					if (types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_RED_BACKGROUND << COLOR_YELLOW << out.str()[symbol_index] << COLOR_RESET;

					else if (types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_YELLOW_BACKGROUND << COLOR_LIGHT_GREEN << out.str()[symbol_index] << COLOR_RESET;
					else if (types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_RED << out.str()[symbol_index] << COLOR_RESET;
					else if (!types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
						std::cout << COLOR_YELLOW_BACKGROUND << COLOR_RED << out.str()[symbol_index] << COLOR_RESET;

					else if (types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
					{
						if (this->world_map.map[i][j].creatures[0]->type_id == 11)
							std::cout << COLOR_GREEN_BACKGROUND << COLOR_BLACK << out.str()[symbol_index] << COLOR_RESET;
						else if (this->world_map.map[i][j].creatures[0]->type_id == 12)
							std::cout << COLOR_DARK_GREEN_BACKGROUND << COLOR_BLACK << out.str()[symbol_index] << COLOR_RESET;
						else
							std::cout << COLOR_PURPLE_BACKGROUND << COLOR_BLACK << out.str()[symbol_index] << COLOR_RESET;
					}
					else if (!types_of_creatures_in_cell[NOf] && types_of_creatures_in_cell[PLANTf] && !types_of_creatures_in_cell[MEATf])
					{
						if (this->world_map.map[i][j].creatures[0]->type_id == 21)
							std::cout << COLOR_YELLOW_BACKGROUND << COLOR_BLACK << out.str()[symbol_index] << COLOR_RESET;
						else if (this->world_map.map[i][j].creatures[0]->type_id == 22)
							std::cout << COLOR_DARK_YELLOW_BACKGROUND << COLOR_BLACK << out.str()[symbol_index] << COLOR_RESET;
					}
					else if (!types_of_creatures_in_cell[NOf] && !types_of_creatures_in_cell[PLANTf] && types_of_creatures_in_cell[MEATf])
					{
						if (this->world_map.map[i][j].creatures[0]->type_id == 31)
							std::cout << COLOR_RED << out.str()[symbol_index] << COLOR_RESET;
						else if (this->world_map.map[i][j].creatures[0]->type_id == 32)
							std::cout << COLOR_LIGHT_RED << out.str()[symbol_index] << COLOR_RESET;
					}
				}
			}
		}
		// clear console
		/*SetConsoleCursorPosition(h, {0, short(this->world_sizes.first + 2)});
		for (int i = 0; i < 166; i++)
		{
			int x = (int)(i % 83);
			int y = (int)(i / 83) + short(this->world_sizes.first + 2);
			//if ((i/ 83) != 0) y += 1;

			COORD symbol_position = { x, y };
			SetConsoleCursorPosition(h, symbol_position);
			std::cout << ' ';
		}*/
		SetConsoleCursorPosition(h, {0, short(this->world_sizes.first + 2)});
		
	}
	this->prev_picture = out.str();
	
	std::cout << COLOR_GREEN << this->count_of_steps << " STEP IS READY" << COLOR_RESET << "\n";
	SetConsoleCursorPosition(h, {20, short(this->world_sizes.first + 3)});
	std::cout << "         ";
	SetConsoleCursorPosition(h, {17, short(this->world_sizes.first + 4)});
	std::cout << "         ";
	SetConsoleCursorPosition(h, {21, short(this->world_sizes.first + 5)});
	std::cout << "         ";
	SetConsoleCursorPosition(h, {20, short(this->world_sizes.first + 6)});
	std::cout << "         ";

	int pl = 0, he = 0, pr = 0;
	for (auto i : this->creatures) {
		if (i->type_of_food == NOf)
			pl++;
		if (i->type_of_food == PLANTf)
			he++;
		if (i->type_of_food == MEATf)
			pr++;
	}

	SetConsoleCursorPosition(h, {0, short(this->world_sizes.first + 3) });
	if (this->creatures.size() > 0)
		std::cout << COLOR_GREEN << "COUNT OF CREATURES: " << this->creatures.size() << COLOR_RESET << "\n";
	else 
		std::cout << COLOR_RED << "COUNT OF CREATURES: " << this->creatures.size() << COLOR_RESET << "\n";

	if (pl > 0)
		std::cout << COLOR_GREEN << "COUNT OF PLANTS: " << pl << COLOR_RESET << "\n";
	else
		std::cout << COLOR_RED << "COUNT OF PLANTS: " << pl << COLOR_RESET << "\n";
	if (he > 1)
		std::cout << COLOR_GREEN << "COUNT OF HERBIVORES: " << he << COLOR_RESET << "\n";
	else
		std::cout << COLOR_RED << "COUNT OF HERBIVORES: " << he << COLOR_RESET << "\n";
	if (pr > 1)
		std::cout << COLOR_GREEN << "COUNT OF PREDATORS: " << pr << COLOR_RESET << "\n";
	else
		std::cout << COLOR_RED << "COUNT OF PREDATORS: " << pr << COLOR_RESET << "\n";

}

std::pair<int, int> World::generate_random_position_for_creature()
{
	std::pair<int, int> random_position;
	bool position_is_unique = true;
	do {
		random_position = std::make_pair(rand() % this->world_sizes.first, rand() % this->world_sizes.second);
		if (this->world_map.map[random_position.first][random_position.second].creatures.size() != 0)
			position_is_unique = false;
		else
			position_is_unique = true;
	} while (position_is_unique != true);
	return random_position;
	//return pair<int, int>();
}

void World::delete_creature(Creature* creature)
{
	if (creature != nullptr) {
		// delete from world
		for (int creature_index = 0; creature_index < (int)this->creatures.size(); creature_index++) {
			if (creature == (this->creatures[creature_index]))
				creatures.erase(creatures.begin() + creature_index);
		}

		// delete from map
		if (this->world_sizes.first >= abs(creature->position.first) && this->world_sizes.second >= abs(creature->position.second)) {
			for (int creature_index = 0; creature_index < (int)this->world_map.map[creature->position.first][creature->position.second].creatures.size(); creature_index++) {
				if (creature == (this->world_map.map[creature->position.first][creature->position.second].creatures[creature_index]))
					this->world_map.map[creature->position.first][creature->position.second].creatures.erase(world_map.map[creature->position.first][creature->position.second].creatures.begin() + creature_index);
			}
		}

		// delete everywhere
		delete creature;
		creature = nullptr;
	}
}


bool World::locate_creature_on_map(Creature* creature)
{
	if (creature->type_of_food == Creature::TYPE_OF_FOOD::NO) {
		short int empty_neighboring_cells[8] = { 0,0,0,0,0,0,0,0 };
		std::pair <int, int> positions_of_near_cells[8];
		
		positions_of_near_cells[0] = std::make_pair(creature->position.first - 1, creature->position.second - 1);
		positions_of_near_cells[1] = std::make_pair(creature->position.first - 1, creature->position.second + 0);
		positions_of_near_cells[2] = std::make_pair(creature->position.first - 1, creature->position.second + 1);
		positions_of_near_cells[3] = std::make_pair(creature->position.first + 0, creature->position.second - 1);
		positions_of_near_cells[4] = std::make_pair(creature->position.first + 0, creature->position.second + 1);
		positions_of_near_cells[5] = std::make_pair(creature->position.first + 1, creature->position.second - 1);
		positions_of_near_cells[6] = std::make_pair(creature->position.first + 1, creature->position.second + 0);
		positions_of_near_cells[7] = std::make_pair(creature->position.first + 1, creature->position.second + 1);
		
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[0], creature) || !this->world_map.check_exist_position(positions_of_near_cells[0]))
			empty_neighboring_cells[0] = 1;
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[1], creature) || !this->world_map.check_exist_position(positions_of_near_cells[1]))
			empty_neighboring_cells[1] = 1;
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[2], creature) || !this->world_map.check_exist_position(positions_of_near_cells[2]))
			empty_neighboring_cells[2] = 1;
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[3], creature) || !this->world_map.check_exist_position(positions_of_near_cells[3]))
			empty_neighboring_cells[3] = 1;
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[4], creature) || !this->world_map.check_exist_position(positions_of_near_cells[4]))
			empty_neighboring_cells[4] = 1;
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[5], creature) || !this->world_map.check_exist_position(positions_of_near_cells[5]))
			empty_neighboring_cells[5] = 1;
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[6], creature) || !this->world_map.check_exist_position(positions_of_near_cells[6]))
			empty_neighboring_cells[6] = 1;
		if (this->world_map.check_creature_with_same_type_in_cell(positions_of_near_cells[7], creature) || !this->world_map.check_exist_position(positions_of_near_cells[7]))
			empty_neighboring_cells[7] = 1;
		

		bool have_empty_neighboring_cells = false;
		for (short int cell_index = 0; cell_index < 8; cell_index++)
			if (empty_neighboring_cells[cell_index] == 0) {
				have_empty_neighboring_cells = true;
				break;
			}

		if (have_empty_neighboring_cells) {

			short int random_way = rand() % 8;
			do {
				random_way = (random_way + 3) % 8;
				//std::cout << COLOR_RED << random_way << COLOR_RESET << "\n";
				if (empty_neighboring_cells[random_way] == 0) {
					switch (random_way)
					{
					case 0:
						creature->position = positions_of_near_cells[0]; break;
					case 1:
						creature->position = positions_of_near_cells[1]; break;
					case 2:
						creature->position = positions_of_near_cells[2]; break;
					case 3:
						creature->position = positions_of_near_cells[3]; break;
					case 4:
						creature->position = positions_of_near_cells[4]; break;
					case 5:
						creature->position = positions_of_near_cells[5]; break;
					case 6:
						creature->position = positions_of_near_cells[6]; break;
					case 7:
						creature->position = positions_of_near_cells[7]; break;
					default:
						break;
					}
				}
			} while (empty_neighboring_cells[random_way] != 0);


			if (!this->world_map.check_creature_with_same_type_in_cell(creature->position, creature)) {
				this->world_map.map[creature->position.first][creature->position.second].creatures.push_back(creature);
				this->creatures.push_back(creature);
				return true;
			}
		}
		else {
			delete creature;
			// this->delete_creature(creature);
			return false;
		}
	}
	else {
		//if (this->world_map.map[creature->position.first][creature->position.second].creatures.size() < 4)
		//{
			creature->position = creature->position;
			this->world_map.map[creature->position.first][creature->position.second].creatures.push_back(creature);
			this->creatures.push_back(creature);
			return true;
		//}
		//else {
		//	delete creature;
		//	return false;
		//}
	}
	return false;
}

void World::counting_creatures()
{
	int count_of_plants = 0, count_of_herbivores = 0, count_of_predators = 0;
	for (int creature_index = 0; creature_index < (int)this->creatures.size(); creature_index++)
	{
		if (this->creatures[creature_index]->type_of_food == NOf)
			count_of_plants++;
		else if (this->creatures[creature_index]->type_of_food == PLANTf)
			count_of_herbivores++;
		else if (this->creatures[creature_index]->type_of_food == MEATf)
			count_of_predators++;
	}
	this->count_of_plants = count_of_plants;
	this->count_of_herbivores = count_of_herbivores;
	this->count_of_predators = count_of_predators;
	return;
}

World::~World()
{
	for (int creature_index = 0; creature_index < (int)this->creatures.size(); creature_index++) {
		delete this->creatures[creature_index];
		this->creatures[creature_index] = nullptr;
	}
}


//WORLDMAP
bool World::WorldMap::check_exist_position(std::pair<int, int> position)
{
	if (position.first < world_sizes.first && position.first >= 0 &&
		position.second < world_sizes.second && position.second >= 0)
		return true;
	else
		return false;
}

bool World::WorldMap::check_creature_with_same_type_in_cell(std::pair <int, int> position, Creature* creature)
{
	if (position.first >= 0  && position.first < this->world_sizes.first &&
		position.second >= 0 && position.second < this->world_sizes.second) {
		for (int i = 0; i < (int)map[position.first][position.second].creatures.size(); i++) {
			//if (dynamic_cast<(typeid(creature))>(map[position.first][position.second].creatures[i]) != nullptr)
			if (typeid(creature) == typeid(map[position.first][position.second].creatures[i]))
				return true;
		}
	}
	return false;
}
