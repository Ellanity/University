import math
import random
from CreatureClass import Creature


class Herbivore(Creature):

    def __init__(self, coords, world):
        super().__init__(world)
        self.parameters = {
            "type_id": 2,
            # "symbol_on_map": "H",
            "symbol_on_map": "▓",
            "coords": coords,
            "viewing_radius": 5,
            "can_change_position": True,
            "distance_it_can_overcome": 4,
            "have_health_points": False,
            "health_points": 1,
            "need_food": True,
            "type_of_food": "PLANT",
            "food_points": 80,
            "need_food_for_one_step": 4,
            "count_of_steps_without_food": 0,
            "count_of_steps_can_live_without_food": 5,
            "chance_to_survive_in_danger_situation": 50,
            "have_size": True,
            "size": 100,
            "age": 0,
            "max_age": 100,
            "can_reproduce_in_neighboring_cell": False,
            "need_a_breeding_partner": True,
            "have_gender": True,
            "count_of_child": 0,
            "gender": random.randint(1, 2)
        }

    def action(self):
        self.parameters["age"] += 1
        if self.parameters["age"] >= self.parameters["max_age"]:
            return "DIE"

        exist_partner_in_cell = False
        exist_food_in_cell = False
        for creature in self.world.map[self.parameters["coords"][0]][self.parameters["coords"][1]].creatures_in_cell:
            if creature.parameters["gender"] != self.parameters["gender"] and \
                    creature.parameters["type_id"] == self.parameters["type_id"] and \
                    creature.possible_for_reproduction() is True and \
                    creature is not self:
                exist_partner_in_cell = True
            if creature.parameters["type_of_food"] == "NO":
                exist_food_in_cell = True

        self.parameters["food_points"] -= self.parameters["need_food_for_one_step"]
        if self.parameters["food_points"] <= 0:
            self.parameters["food_points"] = 0
            self.parameters["count_of_steps_without_food"] += 1
        else:
            self.parameters["count_of_steps_without_food"] = 0

        if self.parameters["count_of_steps_without_food"] > self.parameters["count_of_steps_can_live_without_food"]:
            return "DIE"

        see_food = False
        see_partner = False
        see_danger = False
        r = int(self.parameters["viewing_radius"])
        a = int(self.parameters["coords"][0])
        b = int(self.parameters["coords"][1])
        coords_in_viewing_radius = list()
        for i in range(a - r, a + r):
            for j in range(b - r, b + r):
                if 0 <= i < self.world.world_sizes[0] and 0 <= j < self.world.world_sizes[1] and \
                        ((i - a) ^ 2 + (j - b) ^ 2 <= r ^ 2):
                    coords_in_viewing_radius.append((i, j))
        for coords in coords_in_viewing_radius:
            for creature in self.world.map[coords[0]][coords[1]].creatures_in_cell:
                if creature.parameters["type_of_food"] == "NO":
                    see_food = True
                if creature.parameters["type_of_food"] == "PLANT" and creature is not self and \
                        creature.parameters["gender"] != self.parameters["gender"]:
                    see_partner = True
                if creature.parameters["type_of_food"] == "MEAT":
                    see_danger = True

        if exist_partner_in_cell is True and self.possible_for_reproduction() is True:
            return "REPRODUCTION"
        elif see_partner and self.possible_for_reproduction() is True:
            return "MOVEMENT"

        if exist_food_in_cell is True and see_danger is False and self.parameters["food_points"] < 100: # and \
            #self.world.map[self.parameters["coords"][0]][self.parameters["coords"][1]].creatures_count_with_type("PLANT") < 3:
            return "EATING"
        elif (see_food is True and see_danger is False) or \
                (see_food is True and see_danger is True and self.parameters["food_points"] <= 55):
            return "MOVEMENT"

        return random.choice(["MOVEMENT", "EATING"])

    def action_eating(self, creature_food=None):
        for creature in self.world.map[self.parameters["coords"][0]][self.parameters["coords"][1]].creatures_in_cell:
            if creature.parameters["type_of_food"] == "NO":
                # print("eat:")
                # print("before-eat: food:", self.parameters["food_points"], "size:", self.parameters["size"])
                # print("before-eaten: health:", creature.parameters["health_points"])
                eaten = random.randint(0, 50) + 50
                if eaten > creature.parameters["health_points"]:
                    eaten = creature.parameters["health_points"]
                self.parameters["food_points"] += eaten
                self.parameters["size"] += (eaten / 30)
                self.parameters["need_food_for_one_step"] = self.parameters["size"] / 40
                creature.parameters["health_points"] -= eaten
                # print("after-eat: food:", self.parameters["food_points"], "size:", self.parameters["size"])
                # print("after-eaten: health:", creature.parameters["health_points"])
                return creature
        return None

    def action_movement(self):

        r = int(self.parameters["viewing_radius"])
        a = int(self.parameters["coords"][0])
        b = int(self.parameters["coords"][1])
        coords_in_viewing_radius = list()
        for i in range(a - r, a + r):
            for j in range(b - r, b + r):
                if 0 <= i < self.world.world_sizes[0] and 0 <= j < self.world.world_sizes[1] and \
                        ((i - a) ^ 2 + (j - b) ^ 2 <= r ^ 2):
                    # print((i - a) ^ 2 + (j - b) ^ 2, r ^ 2, i, j)
                    coords_in_viewing_radius.append((i, j))

        # print(coords_in_viewing_radius)
        see_food = False
        see_partner = False
        see_danger = False
        coords_with_food = tuple()
        coords_with_partner = tuple()  # herd instinct
        coords_with_danger = list()
        for coords in coords_in_viewing_radius:
            for creature in self.world.map[coords[0]][coords[1]].creatures_in_cell:
                if creature.parameters["type_of_food"] == "NO" and \
                        creature.parameters["coords"] != self.parameters["coords"]:
                    # print(coords, "plant")
                    if see_food is False:
                        see_food = True
                        coords_with_food = creature.parameters["coords"]
                    else:
                        # (a^2 + b^2 = c^2) => c = sqrt(a ^ 2 + b ^ 2) ### a = abs(x - r)x
                        dist_to_food_it_see = math.sqrt((abs(max(a, creature.parameters["coords"][0]) -
                                                             min(a, creature.parameters["coords"][0])) ^ 2) +
                                                        (abs(max(b, creature.parameters["coords"][1]) -
                                                             min(b, creature.parameters["coords"][1])) ^ 2))
                        dist_to_last_food = math.sqrt((abs(max(a, coords_with_food[0]) -
                                                           min(a, coords_with_food[0])) ^ 2) +
                                                      (abs(max(b, coords_with_food[1]) -
                                                           min(b, coords_with_food[1])) ^ 2))
                        if dist_to_food_it_see < dist_to_last_food:
                            coords_with_food = creature.parameters["coords"]
                    # pass
                if creature.parameters["type_of_food"] == "PLANT" and creature is not self and \
                        creature.parameters["gender"] != self.parameters["gender"]:
                    # print(coords, "partner")
                    if see_partner is False:
                        see_partner = True
                        coords_with_partner = creature.parameters["coords"]
                    else:
                        # (a^2 + b^2 = c^2) => c = sqrt(a ^ 2 + b ^ 2) ### a = abs(x - r)x
                        dist_to_partner_it_see = math.sqrt((abs(max(a, creature.parameters["coords"][0]) -
                                                                min(a, creature.parameters["coords"][0])) ** 2) +
                                                           (abs(max(b, creature.parameters["coords"][1]) -
                                                                min(b, creature.parameters["coords"][1])) ** 2))
                        dist_to_last_partner = math.sqrt((pow(abs(max(a, coords_with_partner[0]) -
                                                                  min(a, coords_with_partner[0])), 2)) +
                                                         pow(abs(max(b, coords_with_partner[1]) -
                                                                 min(b, coords_with_partner[1])), 2))
                        if dist_to_partner_it_see < dist_to_last_partner:
                            coords_with_partner = creature.parameters["coords"]
                if creature.parameters["type_of_food"] == "MEAT":
                    coords_with_danger.append(creature.parameters["coords"])
                    see_danger = True

        endpoint_coords = tuple()
        if see_danger is True and see_partner is False:
            min_sum_of_distances = 0
            for coords in coords_in_viewing_radius:
                sum_of_distances = 0
                for danger in coords_with_danger:
                    x_length = abs(max(coords[0], danger[0]) - min(coords[0], danger[0]))
                    y_length = abs(max(coords[1], danger[1]) - min(coords[1], danger[1]))
                    distance_to_danger = math.sqrt(x_length ** 2 + y_length ** 2)
                    sum_of_distances += distance_to_danger
                if sum_of_distances > min_sum_of_distances:
                    endpoint_coords = coords
            print(self.parameters["coords"], endpoint_coords)
        elif self.possible_for_reproduction() is True and see_partner is True:
            # x_length = abs(max(coords_with_partner[0], self.parameters["coords"][0]) -
            #              min(coords_with_partner[0], self.parameters["coords"][0]))
            # y_length = abs(max(coords_with_partner[1], self.parameters["coords"][1]) -
            #              min(coords_with_partner[1], self.parameters["coords"][1]))

            # print("ok")
            endpoint_coords = coords_with_partner
        elif see_food is True and self.parameters["food_points"]:
            endpoint_coords = coords_with_food
        else:
            endpoint_coords = random.choice(coords_in_viewing_radius)

        dist_horizontal = abs(max(endpoint_coords[0], int(self.parameters["coords"][0])) -
                              min(endpoint_coords[0], int(self.parameters["coords"][0])))
        dist_vertical = abs(max(endpoint_coords[1], int(self.parameters["coords"][1])) -
                            min(endpoint_coords[1], int(self.parameters["coords"][1])))

        distance_to_endpoint = math.sqrt(dist_horizontal ** 2 + dist_vertical ** 2)
        # print("coords before:", self.parameters["coords"])
        # print("endpoint:", endpoint_coords, distance_to_endpoint)
        # print("dist:", "y:", dist_horizontal, "x:", dist_vertical)

        if distance_to_endpoint > self.parameters["distance_it_can_overcome"]:
            # self.parameters["coords"] = endpoint_coords
            # else:
            ratio = distance_to_endpoint / self.parameters["distance_it_can_overcome"]
            dist_horizontal_can_overcome = int(dist_horizontal / ratio)
            dist_vertical_can_overcome = int(dist_vertical / ratio)

            # print("can overcome:", dist_horizontal_can_overcome, dist_vertical_can_overcome, "ratio:", ratio)
            point_to_go = [int(self.parameters["coords"][0]), int(self.parameters["coords"][1])]
            if endpoint_coords[0] < point_to_go[0]:
                point_to_go[0] -= dist_horizontal_can_overcome
            else:
                point_to_go[0] += dist_horizontal_can_overcome

            if endpoint_coords[1] < point_to_go[1]:
                point_to_go[1] -= dist_vertical_can_overcome
            else:
                point_to_go[1] += dist_vertical_can_overcome
            endpoint_coords = (point_to_go[0], point_to_go[1])

        if self.world.map[endpoint_coords[0]][endpoint_coords[1]].creatures_count() < 4:
            # if see_partner is True:
            # print("in cell with partner:", self.world._map[endpoint_coords[0]][endpoint_coords[1]].creatures_count())
            self.world.map[self.parameters["coords"][0]][self.parameters["coords"][1]].creature_remove(self)
            self.parameters["coords"] = endpoint_coords
            self.world.map[self.parameters["coords"][0]][self.parameters["coords"][1]].creature_add(self)

        # print("coords after:", self.parameters["coords"])

    def action_reproduction(self, creature=None):
        self.parameters["count_of_child"] += 1
        self.parameters["food_points"] -= 20
        return Herbivore(self.parameters["coords"], self.world)

    def possible_for_reproduction(self):
        if self.parameters["food_points"] >= 80:
            return True
        else:
            return False
