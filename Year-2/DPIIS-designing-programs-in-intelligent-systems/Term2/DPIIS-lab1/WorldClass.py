import random
import datetime
from PlantClass import Plant
from HerbivoreClass import Herbivore
from PredatorClass import Predator


class World:

    class Cell:
        _coords = tuple()
        _creatures_in_cell = list()

        def __init__(self, coords):
            self._creatures_in_cell = list()
            self._coords = coords

        def creature_add(self, creature):
            if len(self._creatures_in_cell) < 4:
                self._creatures_in_cell.append(creature)
            elif creature.parameters["type_of_food"] == "NO":
                self._creatures_in_cell.append(creature)
            return

        def creature_remove(self, creature):
            self._creatures_in_cell.remove(creature)
            return

        def creatures_count(self):
            return len(self._creatures_in_cell)

        def creatures_count_with_type(self, type_of_food):
            count = 0
            for creature in self._creatures_in_cell:
                if creature.parameters["type_of_food"] == type_of_food:
                    count += 1
            return count

        def presentation(self):
            if len(self._creatures_in_cell) != 0:
                plant = [False, chr(0)]
                herbivore = [False, chr(0)]
                predator = [False, chr(0)]
                for creature in self._creatures_in_cell:
                    if creature.parameters["type_of_food"] == "NO":
                        plant[0] = True
                        plant[1] = creature.parameters["symbol_on_map"]
                    if creature.parameters["type_of_food"] == "PLANT":
                        herbivore[0] = True
                        herbivore[1] = creature.parameters["symbol_on_map"]
                    if creature.parameters["type_of_food"] == "MEAT":
                        predator[0] = True
                        predator[1] = creature.parameters["symbol_on_map"]

                if plant[0] is True and herbivore[0] is True and predator[0] is True:
                    return predator[1]
                elif plant[0] is True and herbivore[0] is True:
                    return herbivore[1]
                elif plant[0] is True and predator[0] is True:
                    return predator[1]
                elif herbivore[0] is True and predator[0] is True:
                    return predator[1]
                elif predator[0] is True:
                    return predator[1]
                elif herbivore[0] is True:
                    return herbivore[1]
                elif plant[0] is True:
                    return plant[1]
            else:
                return "░"

    _creatures = list()
    _world_sizes = tuple()
    _map = list()

    _count_of_plants = 0
    _count_of_herbivores = 0
    _count_of_predators = 0

    def __init__(self, world_sizes):
        self._world_sizes = world_sizes
        for i in range(world_sizes[0]):
            row = list()
            for j in range(world_sizes[1]):
                row.append(World.Cell((i, j)))
            self._map.append(row)

    def creature_generate(self):
        # Generate plants
        plants_count = int((self._world_sizes[0] * self._world_sizes[1]) / ((self._world_sizes[0] +
                                                                             self._world_sizes[1]) / 4))
        # plants_count = 4
        for i in range(plants_count):
            new_plant = Plant(self.creature_find_position(), self)
            self._creatures.append(new_plant)
            x = int(new_plant.parameters["coords"][0])
            y = int(new_plant.parameters["coords"][1])
            # print(f"{i})", x, y, self._map[x][y].creatures_count())
            self._map[x][y].creature_add(new_plant)

        # Generate herbivores
        herbivores_count = int((self._world_sizes[0] * self._world_sizes[1]) / ((self._world_sizes[0] +
                                                                                 self._world_sizes[1]) / 2))
        # herbivores_count = 4
        for i in range(herbivores_count):
            new_herbivore = Herbivore(self.creature_find_position(), self)
            self._creatures.append(new_herbivore)
            x = int(new_herbivore.parameters["coords"][0])
            y = int(new_herbivore.parameters["coords"][1])
            # print(f"{i})", x, y, self._map[x][y].creatures_count())
            self._map[x][y].creature_add(new_herbivore)

        # Generate predators
        predators_count = int((self._world_sizes[0] * self._world_sizes[1]) / ((self._world_sizes[0] +
                                                                                 self._world_sizes[1])))
        # predators_count = 4
        for i in range(predators_count):
            new_predators = Predator(self.creature_find_position(), self)
            self._creatures.append(new_predators)
            x = int(new_predators.parameters["coords"][0])
            y = int(new_predators.parameters["coords"][1])
            # print(f"{i})", x, y, self._map[x][y].creatures_count())
            self._map[x][y].creature_add(new_predators)

        self._count_of_plants += plants_count
        self._count_of_herbivores += herbivores_count
        self._count_of_predators += predators_count

    def creature_find_position(self, creature=None):
        random.seed(datetime.datetime.now())
        while True:
            x = random.randint(0, self._world_sizes[0] - 1)
            y = random.randint(0, self._world_sizes[1] - 1)
            random_position = (x, y)
            if (creature is None) and \
                    (self._map[x][y].creatures_count() == 0):
                return random_position
            elif (creature is not None) and \
                    (self._map[x][y].creatures_count_with_type(creature.parameters["type_of_food"])):
                return random_position

    def creature_locate(self, creature):
        if creature.parameters["type_of_food"] == "NO":
            empty_cells_near = {
                (creature.parameters["coords"][0] - 1, creature.parameters["coords"][1] - 1): False,
                (creature.parameters["coords"][0] - 1, creature.parameters["coords"][1] + 0): False,
                (creature.parameters["coords"][0] - 1, creature.parameters["coords"][1] + 1): False,
                (creature.parameters["coords"][0] + 0, creature.parameters["coords"][1] - 1): False,
                (creature.parameters["coords"][0] + 0, creature.parameters["coords"][1] + 1): False,
                (creature.parameters["coords"][0] + 1, creature.parameters["coords"][1] - 1): False,
                (creature.parameters["coords"][0] + 1, creature.parameters["coords"][1] + 0): False,
                (creature.parameters["coords"][0] + 1, creature.parameters["coords"][1] + 1): False
            }
            have_empty_cells_near = False
            for coords in empty_cells_near:
                if (0 <= coords[0] < self._world_sizes[0]) and (0 <= coords[1] < self._world_sizes[1]) and \
                        self._map[coords[0]][coords[1]].creatures_count_with_type("NO") == 0:
                    empty_cells_near[coords] = True
                    have_empty_cells_near = True

            if have_empty_cells_near is True:
                empty_cells_near_list = list(empty_cells_near)
                while True:
                    way = random.choice(empty_cells_near_list)
                    if empty_cells_near[way] is True:
                        creature.parameters["coords"] = way
                        # print("new plant:", creature.parameters["coords"],
                        #       f"in cell {way} with {self._map[way[0]][way[1]].creatures_count_with_type('NO')} plants")
                        self._count_of_plants += 1
                        self._creatures.append(creature)
                        self._map[way[0]][way[1]].creature_add(creature)
                        break
            else:
                self.creature_remove(creature)
        else:
            if self._map[creature.parameters["coords"][0]][creature.parameters["coords"][1]].creatures_count() < 4:
                if creature.parameters["type_of_food"] == "PLANT":
                    self._count_of_herbivores += 1
                if creature.parameters["type_of_food"] == "MEAT":
                    self._count_of_predators += 1
                self._creatures.append(creature)
                self._map[creature.parameters["coords"][0]][creature.parameters["coords"][1]].creature_add(creature)

    def creature_add(self, creature, coords):
        pass

    def creature_remove(self, creature):
        try:
            self._map[creature.parameters["coords"][0]][creature.parameters["coords"][1]].creature_remove(creature)
            self._creatures.remove(creature)
            if creature.parameters["type_of_food"] == "NO":
                self._count_of_plants -= 1
            if creature.parameters["type_of_food"] == "PLANT":
                self._count_of_herbivores -= 1
            if creature.parameters["type_of_food"] == "MEAT":
                self._count_of_predators -= 1
        except:
            pass

    def step_generate(self):
        creatures_to_locate = []
        # creatures_to_remove = []

        creatures_previous_step = self._creatures.copy()
        for creature in creatures_previous_step:
            result = creature.action()
            # if creature.parameters["type_of_food"] == "PLANT":
            # print(f"{creature.parameters.get('type_id')})", creature.parameters["coords"], result)

            if result == "NO":
                pass
            elif result == "REPRODUCTION":
                new_creature = creature.action_reproduction()
                creatures_to_locate.append(new_creature)
            elif result == "EATING":
                eaten_creature = creature.action_eating()
                if eaten_creature is not None and eaten_creature.parameters["health_points"] <= 0:
                    # ("plat die(h): ", eaten_creature.parameters["coords"])
                    self.creature_remove(eaten_creature)
                    creatures_previous_step.remove(eaten_creature)
            elif result == "MOVEMENT":
                creature.action_movement()
            elif result == "DIE":
                # if creature.parameters["type_id"] == 1:
                #    print("plant die: ", creature.parameters["coords"])
                self.creature_remove(creature)
                creatures_previous_step.remove(creature)

        for creature in creatures_to_locate:
            self.creature_locate(creature)

        """ 
        Тут крч ошибка скорее всего когда-то выскочит. 
        В том случае если несколько существ будут пытаться занять одну
        клетку locate расположение не укажет для остальных существ
        """
        # for creature in creatures_to_locate:
        #     self.creature_locate(creature)

    def step_print(self):
        for row in self._map:
            row_str = ""
            for cell in row:
                row_str += cell.presentation()
            print(row_str)

    def step_save(self):
        pass

    def command(self, command):
        #if command == "info -h all":
        if command == "iha":
            for creature in self._creatures:
                if creature.parameters["type_of_food"] == "PLANT":
                    print(creature.parameters)
            return True
        if command == "iga":
            for creature in self._creatures:
                if creature.parameters["type_of_food"] == "NO":
                    print(creature.parameters)
            return True
        # count of grass in coords
        com = command.split(" ")
        if com[0] == "cgc" and len(com) == 3:
            x = int(com[1])
            y = int(com[2])
            print(self._map[x][y].creatures_count_with_type('NO'))
            return True
        elif com[0] == "cgc":
            for i in range(0, self._world_sizes[0]):
                for j in range(0, self._world_sizes[1]):
                    print(f"{i} {j})", self._map[i][j].creatures_count_with_type('NO'))
            return True
        if com[0] == "chc" and len(com) == 3:
            x = int(com[1])
            y = int(com[2])
            print(self._map[x][y].creatures_count_with_type('PLANT'))
            return True
        elif com[0] == "chc":
            for i in range(0, self._world_sizes[0]):
                for j in range(0, self._world_sizes[1]):
                    print(f"{i} {j})", self._map[i][j].creatures_count_with_type('PLANT'))
            return True
        return False