import os
import time

from WorldClass import World


def main():
    #world = World((2, 4))
    world = World((8, 50))
    #world = World((15, 100))
    world.creature_generate()
    world.step_print()
    while True:
        next_step = input()
        result = world.command(next_step)
        if next_step is not None and result is False:
            world.step_generate()
            os.system("cls")
            world.step_print()
            print("all:", len(world._creatures), "plants:", world._count_of_plants,
                  "herbivores:", world._count_of_herbivores,
                  "predators:", world._count_of_predators)
            # time.sleep(0.01)

"""
Доделать
 - сохранение в файл
 - добавление существ на клетку поля
 - сбалансировать мир, что бы дольше работал 
Исправлено
 + то что predators не размножаются
 + где-то идет неправильный подсчет herbivores и predators 
 // на самом деле они размножались, а счетчик накидывал не туда, это одна ошибка
"""


if __name__ == "__main__":
    main()
