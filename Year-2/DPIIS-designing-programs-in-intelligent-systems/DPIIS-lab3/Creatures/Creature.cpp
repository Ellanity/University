#include "Creature.h"

//Creature::RESULT_OF_EATING Creature::eating()
//{
//    if (need_food == true)
//    {
//        if (food_points == 0)
//            count_of_steps_without_food++;
//        if (food_points == )
//    }
//    TYPE_OF_FOOD type_of_food;
//}

/*
std::pair<int, int> Creature::generate_random_position(std::vector <Creature*>& creatures,
    std::pair <int, int> world_size, std::vector < std::pair<int, int> >& occupied_positions)
{
    //std::vector < std::pair<int, int> > occupied_positions;
    std::pair<int, int> random_position;
    bool position_is_unique = true;
    do {
        random_position = std::make_pair((rand() + world_size.first) % world_size.first, (rand() + world_size.second) % world_size.second);
        for (int position_index = 0; position_index < occupied_positions.size(); position_index++) {
            if (random_position.first == occupied_positions[position_index].first&&
                random_position.second == occupied_positions[position_index].second)
            {
                position_is_unique = false;
                break;
            }
            if (position_index == occupied_positions.size() - 1)
                position_is_unique = true;
        }
    } while (position_is_unique != true);
    return random_position;
}*/
