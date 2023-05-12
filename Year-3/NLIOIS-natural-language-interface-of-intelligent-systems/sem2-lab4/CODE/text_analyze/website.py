import random

website_url_list = []

def read_website_urls():
    global website_url_list
    for i in open(r'D:\Uni\3 курс\ЕЯзИИС\lab4\site\site.txt','r'):
        website_url_list.append(i[:-1])

def get_site():
    read_website_urls()
    print(random.choice(website_url_list))
    return random.choice(website_url_list)


