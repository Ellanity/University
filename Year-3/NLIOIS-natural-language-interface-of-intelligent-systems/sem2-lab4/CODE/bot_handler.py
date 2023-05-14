import random
import os
import json
import telebot

import text_analyze.check_films
import text_analyze.website
import text_analyze.check_books

from help_texts.main_help import MAINHELP

bot = telebot.TeleBot("id:token")
bot_command_key = dict()
path = os.getcwd()

# bot_command_video=False
# bot_command_site=False
# bot_command_book=False

sorry_answer = "Sorry, I can't help you :("


def get_dialogs():
    with open(os.getcwd() + '/dialog_handler/dialog.json', 'r', encoding='utf-8') as file:
        data = file.read().strip()
    return json.loads(data)


@bot.message_handler(commands=['start'])
def start_message_handler(message):
    bot.send_message(message.chat.id, 'Hi, can I help you?', reply_markup=keyboard)


@bot.message_handler(commands=['help'])
def help_message_handler(message):
    bot.send_message(message.chat.id, 'I can help with the search for various materials related to leisure time', reply_markup=keyboard)


@bot.message_handler(content_types=['text'])
def send_text(message):
    global bot_command_key

    #  global bot_command_video
    #  global bot_command_site
    #  global bot_command_book

    key = False

    if 'video' in message.text.lower():
        # bot_command_video = True
        #  key=True
        bot_command_key[message.chat.id] = 'video'
        bot.send_message(message.chat.id, "Well, now I'll pick something...")
    elif 'book' in message.text.lower():
        key = True
        # bot_command_book = True
        bot_command_key[message.chat.id] = 'book'
        bot.send_message(message.chat.id, "Do you want to find something about fantasy, history or science?\n Just let me know.")
    elif 'site' in message.text.lower():
        # key=True
        # bot_command_site = True
        bot_command_key[message.chat.id] = 'site'
        bot.send_message(message.chat.id, "Well, now I'll see what's interesting...")

    if not key and message.chat.id in bot_command_key and len(bot_command_key[  message.chat.id]) > 0:
        if bot_command_key[message.chat.id] == 'video':
            answer = text_analyze.check_films.get_video()
            bot.send_message(message.chat.id, f"Here, there is:{answer}")

        elif bot_command_key[message.chat.id] == 'book':
            bot.send_message(message.chat.id, "Here, I found something:")
            bot.send_photo(message.chat.id, text_analyze.check_books.find_books(message.text))
        #    bot_command_book = True

        elif bot_command_key[message.chat.id] == 'site':
            answer = text_analyze.website.get_site()
            bot.send_message(message.chat.id, f"Here is a site:{answer}")
        #   bot_command_site = False

        # сброс
        bot_command_key[message.chat.id] = ''
    # key=False

    elif not key:
        # Просто случайные ответы
        dialogs = get_dialogs()
        answer_key = False
        for dialog in dialogs:
            if message.text.lower() in dialog['question'].lower():
                answer_key = True
                answers = list(dialog['answer'].split('|'))
                bot.send_message(message.chat.id, answers[random.randint(0, len(answers) - 1)])
                break
        if answer_key is False:
            bot.send_message(message.chat.id, sorry_answer)


keyboard = telebot.types.ReplyKeyboardMarkup(True, True, True)

keyboard.row('Help me find an interesting site for leisure time')
keyboard.row('Help me find some video')
keyboard.row('Help me find an interesting book')
keyboard.row('Help')
