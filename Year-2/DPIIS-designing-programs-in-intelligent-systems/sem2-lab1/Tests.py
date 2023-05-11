import unittest
from WorldClass import World
from PlantClass import Plant
from HerbivoreClass import Herbivore
from PredatorClass import Predator


class TestCell(unittest.TestCase):

    def setUp(self):
        self.cell = World.Cell((0, 0))
        self.plant = Plant((0, 0), self)
        self.herbivore = Herbivore((0, 0), self)
        self.predator = Predator((0, 0), self)
        self.cell.creatures_in_cell = [self.plant, self.herbivore, self.predator]

    def test_creature_add(self):
        plant = Plant((0, 0), self)
        self.cell.creature_add(plant)
        self.assertEqual(self.cell.creatures_in_cell, [self.plant, self.herbivore, self.predator, plant])

    def test_creature_remove(self):
        self.cell.creature_remove(self.predator)
        self.cell.creature_remove(self.plant)
        self.assertEqual(self.cell.creatures_in_cell, [self.herbivore])

    def test_creatures_count(self):
        self.assertEqual(self.cell.creatures_count(), 3)

    def test_creatures_count_with_type(self):
        self.assertEqual(self.cell.creatures_count_with_type("NO"), 1)

    def test_presentation(self):
        self.assertEqual(self.cell.presentation(), self.predator.parameters["symbol_on_map"])


class TestWorld(unittest.TestCase):

    def setUp(self):
        self.world = World((8, 50))
        self.herbivore = Herbivore((7, 7), self.world)

    def test_creature_generate(self):
        self.world.creature_generate()
        self.assertEqual(self.world.count_of_predators, 13)
        self.assertEqual(self.world.count_of_plants, 13)
        self.assertEqual(self.world.count_of_herbivores, 13)

    def test_creature_locate(self):
        self.world.map[0][0].creature_add(Plant((0, 0), self.world))
        self.world.map[0][1].creature_add(Plant((0, 1), self.world))
        self.world.map[0][2].creature_add(Plant((0, 2), self.world))
        self.world.map[1][0].creature_add(Plant((1, 0), self.world))
        self.world.map[1][2].creature_add(Plant((1, 2), self.world))
        self.world.map[2][0].creature_add(Plant((2, 0), self.world))
        self.world.map[2][1].creature_add(Plant((2, 1), self.world))
        # self.world.map[2][2].creature_add(Plant((2, 2), self.world))
        for creature in self.world.map[2][2].creatures_in_cell:  # clear cell
            self.world.map[2][2].creature_remove(creature)
        plant = Plant((1, 1), self.world)
        self.world.creature_locate(plant)  # <= main row
        self.assertEqual(self.world.map[2][2].creatures_in_cell, [plant])

    def test_creature_add(self):
        for creature in self.world.map[7][7].creatures_in_cell:
            self.world.map[7][7].creature_remove(creature)
        self.world.creature_add(self.herbivore, (7, 7))
        self.assertEqual(self.world.map[7][7].creatures_in_cell, [self.herbivore])

    def test_creature_remove(self):
        for creature in self.world.map[7][7].creatures_in_cell:
            self.world.map[7][7].creature_remove(creature)  # clear
        self.world.creature_add(self.herbivore, (7, 7))  # add
        self.world.creature_remove(self.herbivore)  # remove
        self.assertEqual(self.world.map[7][7].creatures_in_cell, [])
        self.assertEqual(self.herbivore in self.world.creatures, False)

    def test_command(self):
        for creature in self.world.map[5][5].creatures_in_cell:
            self.world.map[5][5].creature_remove(creature)  # clear
        self.world.command("ag 5 5")
        self.world.command("ah 5 5")
        self.world.command("ah 5 5")
        self.world.command("ap 5 5")
        self.assertEqual([self.world.map[5][5].creatures_count_with_type("NO"),
                          self.world.map[5][5].creatures_count_with_type("PLANT"),
                          self.world.map[5][5].creatures_count_with_type("MEAT")], [1, 2, 1])

