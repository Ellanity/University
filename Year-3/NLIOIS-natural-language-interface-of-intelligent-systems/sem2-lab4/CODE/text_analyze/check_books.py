import random
import os

path_main = os.getcwd()
path_for_items = path_main + '/books/'


def find_books(message):
    if message.find('fantasy') != -1:
        branch = "fantasy"
        DIR = path_for_items+'/'+branch
        return open(os.path.join(DIR, random.choice(os.listdir(DIR))), 'rb')
    elif message.find('history') != -1:
        branch = "history"
        DIR = path_for_items+'/'+branch
        return open(os.path.join(DIR, random.choice(os.listdir(DIR))), 'rb')
    elif message.find('science') != -1:
        branch = "science"
        DIR = path_for_items+'/'+branch
        return open(os.path.join(DIR, random.choice(os.listdir(DIR))), 'rb')
    else:
        return open(path_main+'/error.jpg', 'rb')


