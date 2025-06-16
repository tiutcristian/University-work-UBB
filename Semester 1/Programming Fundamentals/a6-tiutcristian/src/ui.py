#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements)
# are found here
#
from functions import *
import datetime


def read() -> list:
    input_text = input(">>>").strip()
    words = input_text.split(" ")
    return words


def interpret_input(words: list[str], history: list[list]):
    if words[0].lower() == "add" or words[0].lower() == "insert":
        history.append(interpret_add(words, history[len(history) - 1]))
        return history
    elif words[0].lower() == "remove":
        history.append(interpret_remove(words, history[len(history) - 1]))
        return history
    elif words[0].lower() == "list":
        interpret_display(words, history[len(history) - 1])
        return history
    elif words[0].lower() == "filter":
        history.append(interpret_filter(words, history[len(history) - 1]))
        return history
    elif words[0].lower() == "undo":
        return interpret_undo(words, history)
    elif words[0].lower() == "exit":
        if interpret_exit(words):
            return "x"
    else:
        raise ValueError("Error! Command unavailable.")


def interpret_add(words: list[str], expenses_list: list):
    if len(words) == 3:  # add <sum> <category>
        if words[0].lower() == "add" and words[1].isdigit():
            x = datetime.datetime.now()
            curr_day = x.strftime("%d")
            if curr_day == 31:
                curr_day = 30
            return add_new_expense(int(curr_day), int(words[1]), words[2], expenses_list)
        else:
            raise ValueError("Error! Wrong input format!")
    elif len(words) == 4:
        if words[0].lower() == "insert" and words[1].isdigit() and words[2].isdigit():
            return add_new_expense(int(words[1]), int(words[2]), words[3], expenses_list)
        else:
            raise ValueError("Error! Wrong input format!")
    else:
        raise ValueError("Error! Wrong input format!")


def interpret_remove(words: list[str], expenses_list: list):
    if len(words) == 4:  # interval of days case
        if words[1].isdigit() and words[2].lower() == "to" and words[3].isdigit():
            return remove(int(words[1]), int(words[3]), expenses_list)
        else:
            raise ValueError("Error! Wrong input format!")
    elif len(words) == 2:
        if words[1].isdigit():  # day case
            return remove(int(words[1]), int(words[1]), expenses_list)
        else:  # category case
            return remove_category(words[1], expenses_list)
    else:
        raise ValueError("Error! Wrong input format!")


def interpret_display(words: list[str], expenses_list: list):
    if len(words) == 1:  # list
        print_list(expenses_list)
    elif len(words) == 2:  # list <category>
        tmp_list = filter_expenses(expenses_list, -1, -1, words[1])
        print_list(tmp_list)
    elif len(words) == 4 and words[3].isdigit():  # list <category> [ < | = | > ] <value>
        if words[2] == '<':
            tmp_list = filter_expenses(expenses_list, -1, int(words[3]) - 1, words[1])
            print_list(tmp_list)
        elif words[2] == '=':
            tmp_list = filter_expenses(expenses_list, int(words[3]), int(words[3]), words[1])
            print_list(tmp_list)
        elif words[2] == '>':
            tmp_list = filter_expenses(expenses_list, int(words[3]) + 1, -1, words[1])
            print_list(tmp_list)
        else:
            raise ValueError("Error! Wrong input format!")
    else:
        raise ValueError("Error! Wrong input format!")


def interpret_filter(words: list[str], expenses_list: list):
    if len(words) == 2:  # filter <category>
        return filter_expenses(expenses_list, -1, -1, words[1])
    elif len(words) == 4 and words[3].isdigit():  # list <category> [ < | = | > ] <value>
        if words[2] == '<':
            return filter_expenses(expenses_list, -1, int(words[3]) - 1, words[1])
        elif words[2] == '=':
            return filter_expenses(expenses_list, int(words[3]), int(words[3]), words[1])
        elif words[2] == '>':
            return filter_expenses(expenses_list, int(words[3]) + 1, -1, words[1])
        else:
            raise ValueError("Error! Wrong input format!")
    else:
        raise ValueError("Error! Wrong input format!")


def interpret_undo(words: list, history: list) -> list:
    if len(words) == 1:
        return undo(history)
    else:
        raise ValueError("Error! Command unavailable.")


def interpret_exit(words: list):
    if len(words) > 1:
        raise ValueError("Error! Command unavailable.")
    elif words[0].lower() == "exit":
        return True
    else:
        raise ValueError("Error! Command unavailable.")


def run_UI():
    history = [initial_list()]
    print("\nHello!"
          "\nUse one of the following command formats to manipulate your expenses list:"
          "\n1. To add expenses:"
          "\n     \"add <sum> <category>\""
          "\n     \"insert <day> <sum> <category>\""
          "\n"
          "\n2. To remove expenses:"
          "\n     \"remove <day>\""
          "\n     \"remove <start day> to <end day>\""
          "\n     \"remove <category>\""
          "\n"
          "\n3. To display expenses with different properties"
          "\n     \"list\""
          "\n     \"list <category>\""
          "\n     \"list <category> [ < | = | > ] <value>\""
          "\n"
          "\n4. To filter expenses:"
          "\n     \"filter <category>\""
          "\n     \"filter <category> [ < | = | > ] <value>\""
          "\n"
          "\n5. To undo changes:"
          "\n     \"undo\""
          "\n"
          "\n6. To exit the app:"
          "\n     \"exit\"")
    while True:
        user_input = read()
        try:
            interpretation = interpret_input(user_input, history)
            if interpretation == "x":
                print("Goodbye!")
                break
            else:
                history = interpretation
        except ValueError as ve:
            print(ve)
