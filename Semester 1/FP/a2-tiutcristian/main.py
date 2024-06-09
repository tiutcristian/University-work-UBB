import random

# Functions & Methods -------------------------------------
def read_option():
    """
    Read option
    :return: option 1-4 or -1 if input is not a digit from 1 to 4
    """
    option = input("Choose option: ").strip()
    if option.isdigit():
        return int(option)
    return -1


def create_random_list(n: int) -> list:
    """
    Generates a random list of numbers between 0 and 100
    :param n: number of elements in the list
    :return: generated list
    """
    new_list = []
    # TODO! (numbers between 0 and 100)
    for i in range(n):
        new_list.append(random.randint(0, 100))
    return new_list


def option1_handler() -> list:
    """
    Handles option 1
    :return: generated numbers list
    """
    length_user_input = input('Enter the length of the list (max. 1 million): ').strip()
    while True:  # get out of loop only if number provided
        if not length_user_input.isdigit():  # we won't accept other characters than numbers
            length_user_input = input("Error! Please enter a natural number: ").strip()
        elif int(length_user_input) > 1000000:  # we will limit the number of elements of the list to 1 million
            length_user_input = input("Error! Please enter a number smaller than 1 million: ").strip()
        else:
            number_list = create_random_list(int(length_user_input))
            print("Generated list: ", number_list)
            return number_list


def increment_steps(curr_step: int, steps_reset: int, number_list: list) -> int:
    """
    Increment the number of steps done by an algorithm
    :param curr_step: steps counter
    :param steps_reset: point where steps counter is reset and numbers list is printed
    :param number_list: list of numbers
    :return: incremented/reset steps counter
    """
    if curr_step + 1 == steps_reset:
        print(number_list)
        return 0
    return curr_step + 1


def exchange_sort(number_list: list, steps: int) -> list:
    """
    Exchange sort function that prints final list every 'steps' steps
    :param number_list: list of numbers
    :param steps: number of operations after which steps counter is reset and numbers list is printed
    :return: sorted list of numbers
    """
    current_step = 0
    for i in range(0, len(number_list) - 1):
        for j in range(i + 1, len(number_list)):
            if number_list[i] > number_list[j]:
                number_list[i], number_list[j] = number_list[j], number_list[i]
                # every swap is a step
                current_step = increment_steps(current_step, steps, number_list)
    return number_list


def option2_handler(number_list: list) -> list:
    """
    Handles option 2
    :param number_list: list of numbers
    :return: sorted numbers list
    """
    if number_list:
        print("You chose exchange sort.")
        steps_user_input = input("Enter step at which to print the list: ").strip()
        while True:
            if steps_user_input.isdigit():
                steps = int(steps_user_input)
                number_list = exchange_sort(number_list, steps)
                print("Final list:\n", number_list)
                return number_list
            else:
                steps_user_input = input("Error! Please enter a number: ").strip()
    else:
        print("Create a random numbers list first! (option 1)")


def merge_lists(list1: list, list2: list) -> list:
    """
    Merge 2 lists
    :param list1: 1st list
    :param list2: 2nd list
    :return: the result list after merging the 2 lists
    """
    result = []
    while list1 and list2:
        if list1[0] < list2[0]:
            result.append(list1[0])
            list1.pop(0)
        else:
            result.append(list2[0])
            list2.pop(0)
    while list1:
        result.append(list1[0])
        list1.pop(0)
    while list2:
        result.append(list2[0])
        list2.pop(0)
    return result


def strand_sort(number_list: list, steps: int) -> list:
    """
    Strand sort function that prints final list every 'steps' steps
    :param number_list: list of numbers
    :param steps: number of operations after which steps counter is reset and numbers list is printed
    :return: sorted list of numbers
    """
    current_step = 0
    final_list = []
    while number_list:
        # Start building aux_list
        aux_list = [number_list[0]]
        number_list.pop(0)

        # iterate through number_list
        i = 0
        while i < len(number_list):
            if number_list[i] >= aux_list[len(aux_list) - 1]:
                aux_list.append(number_list[i])  # add elements increasingly to aux_list
                number_list.pop(i)               # and pop them from number_list
            else:
                i += 1

        # Merge aux_list with final_list
        final_list = merge_lists(aux_list, final_list)
        current_step = increment_steps(current_step, steps, final_list)
    return final_list


def option3_handler(number_list: list):
    """
        Handles option 3
        :param number_list: list of numbers
        :return: sorted numbers list
        """
    if number_list:
        print("You chose strand sort.")
        steps_user_input = input("Enter step at which to print the list: ").strip()
        while True:
            if steps_user_input.isdigit():
                steps = int(steps_user_input)
                number_list = strand_sort(number_list, steps)
                print("Final list:\n", number_list)
                return number_list
            else:
                steps_user_input = input("Error! Please enter a number: ").strip()
    else:
        print("Create a random numbers list first! (option 1)")


# Variables -------------------------------------
menu_text = ("\n--------- Menu ---------"
             "\n1. Create a random list"
             "\n2. Exchange sort"
             "\n3. Strand sort"
             "\n4. Exit"
             "\n------------------------")
numbers_list = []

# Main -------------------------------------
while True:
    print(menu_text)
    option = read_option()
    if option == 1:
        numbers_list = option1_handler()
    elif option == 2:  # exchange sort
        numbers_list = option2_handler(numbers_list)
    elif option == 3:  # strand sort
        numbers_list = option3_handler(numbers_list)
    elif option == 4:
        print("Bye!")
        break
    else:
        print("Error! Please enter a number between 1 and 4!")
