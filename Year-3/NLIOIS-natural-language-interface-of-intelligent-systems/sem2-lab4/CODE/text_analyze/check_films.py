import random
import os
video_url_list = []

def read_video_urls():
    global video_url_list
    for i in open(r'D:\Uni\3 курс\ЕЯзИИС\lab4\video\videos.txt', 'r'):
        video_url_list.append(i[:-1])


def get_video():
    read_video_urls()
    print(random.choice(video_url_list))
    return random.choice(video_url_list)