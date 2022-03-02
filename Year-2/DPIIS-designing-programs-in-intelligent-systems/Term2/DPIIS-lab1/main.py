import os
import pickle

from WorldClass import World


def main():
    print("start - new game\nload  - load game from file")
    first_command = input()
    os.system("cls")
    if first_command == "start" or first_command == "":
        world = World((8, 50))
        # world = World((2, 4))
        # world = World((15, 100))
        world.creature_generate()
        world.step_print()
    else:
        file = open(r'saved_game.txt', 'rb')
        world = pickle.load(file)

        for i in range(0, world.world_sizes[0]):
            row = list()
            for j in range(0,  world.world_sizes[1]):
                cell = pickle.load(file)
                for creature in cell.creatures_in_cell:
                    world.creatures.append(creature)
                row.append(cell)
            world.map.append(row)

            # world.map[cell.coords[0]][cell.coords[1]] = cell

        for creature in range(1, (world.count_of_plants + world.count_of_herbivores + world.count_of_predators)):
            creature = pickle.load(file)
            # world.creatures.append(creature)
            # world.map[creature.parameters["coords"][0]][creature.parameters["coords"][1]].creature_add(creature)
        file.close()

    # first screen
    world.step_print()
    print_short_world_info(world)

    while True:
        try:
            step = input()
            it_is_command = False
            # global commands
            if step == "save":

                file = open(r'saved_game.txt', 'wb')

                pickle.dump(world, file)
                for row_i in range(world.world_sizes[0]):
                    for cell_j in range(world.world_sizes[1]):
                        pickle.dump(world.map[row_i][cell_j], file)
                for creature in world.creatures:
                    pickle.dump(creature, file)

                file.close()

                print("saved")
                it_is_command = True
            if step == "exit":
                exit()
                pass

            if it_is_command is False:
                it_is_command = world.command(step)
                pass

            if step is not None and it_is_command is False:
                world.step_generate()
                os.system("cls")
                world.step_print()
                print_short_world_info(world)
                # time.sleep(0.01)
        except Exception as ex:
            print(ex)


def print_short_world_info(world):
    print("step:", world.count_of_steps, "\nall:", len(world.creatures), "plants:", world.count_of_plants,
          "herbivores:", world.count_of_herbivores,
          "predators:", world.count_of_predators)

"""
Доделать
 - сбалансировать мир, что бы дольше работал 
Исправлено
 + сохранение в файл
 + добавление существ на клетку поля
 """


if __name__ == "__main__":
    main()
