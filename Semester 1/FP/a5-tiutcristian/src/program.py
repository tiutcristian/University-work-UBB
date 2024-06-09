#
# Write the implementation for A5 in this file
#
import math
import random


#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
# def create_complex_number(real: int, im: int) -> list:
#     new_list = [real, im]
#     return new_list
#
#
# def get_real(complex_number: list) -> int:
#     return complex_number[0]
#
#
# def get_imaginary(complex_number: list) -> int:
#     return complex_number[1]
#
#
# def set_real(complex_number: list, value: int) -> list:
#     complex_number[0] = value
#     return complex_number
#
#
# def set_imaginary(complex_number: list, value: int) -> list:
#     complex_number[1] = value
#     return complex_number
#
#
# def complex_to_str(complex_number: list) -> str:
#     if complex_number[1] > 0:
#         return f"{complex_number[0]}+{complex_number[1]}i"
#     elif complex_number[1] < 0:
#         return f"{complex_number[0]}{complex_number[1]}i"
#     else:
#         return f"{complex_number[0]}"
#
#
# def str_to_complex(complex_number_string: str) -> list:
#     if complex_number_string.find("+") != -1:                       # addition
#         tmp = complex_number_string.split("+")
#         return create_complex_number(int(tmp[0]), int(tmp[1][:-1]))
#     elif complex_number_string.find("-") != -1:                     # subtraction
#         tmp = complex_number_string.split("-")
#         return create_complex_number(int(tmp[0]), -int(tmp[1][:-1]))
#     else:                                                           # no imaginary part
#         return create_complex_number(int(complex_number_string), 0)


#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def create_complex_number(real: int, im: int) -> dict:
    new_dict = {"real": real, "img": im}
    return new_dict


def get_real(complex_number: dict) -> int:
    return complex_number["real"]


def get_imaginary(complex_number: dict) -> int:
    return complex_number["img"]


def set_real(complex_number: dict, value: int) -> dict:
    complex_number["real"] = value
    return complex_number


def set_imaginary(complex_number: dict, value: int) -> dict:
    complex_number["img"] = value
    return complex_number


def complex_to_str(complex_number: dict) -> str:
    if complex_number['img'] > 0:
        return f"{complex_number['real']}+{complex_number['img']}i"
    elif complex_number['img'] < 0:
        return f"{complex_number['real']}{complex_number['img']}i"
    else:
        return f"{complex_number['real']}"


def str_to_complex(complex_number_string: str) -> dict:
    if complex_number_string.find("+") != -1:                       # addition
        tmp = complex_number_string.split("+")
        return create_complex_number(int(tmp[0]), int(tmp[1][:-1]))
    elif complex_number_string.find("-") != -1:                     # subtraction
        tmp = complex_number_string.split("-")
        return create_complex_number(int(tmp[0]), -int(tmp[1][:-1]))
    else:                                                           # no imaginary part
        return create_complex_number(int(complex_number_string), 0)


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def create_initial_list() -> list:
    number_list = [
        create_complex_number(
            random.randint(0, 10),
            random.randint(0, 10)
        )
        for i in range(10)
    ]
    return number_list


def modulus(real: int, img: int) -> float:
    return math.sqrt(real ** 2 + img ** 2)


def generate_modulus_list(number_list: list) -> list:
    mod_list = []
    for number in number_list:
        mod_list.append(modulus(get_real(number), get_imaginary(number)))
    return mod_list


def naive_pb_5(number_list: list) -> tuple[int, list]:
    mod_list = generate_modulus_list(number_list)
    n = len(number_list)
    left_max = 0
    right_max = -1
    for left in range(n - 1):
        for right in range(1, n):
            is_valid = True
            for i in range(left, right + 1):
                if mod_list[i] > 10:
                    is_valid = False
            if is_valid and right - left > right_max - left_max:
                left_max = left
                right_max = right
    return right - left + 1, number_list[left:(right + 1)]


def generate_real_part_list(number_list: list) -> list:
    real_list = []
    for number in number_list:
        real_list.append(get_real(number))
    return real_list


def dynamic_pb_12(number_list: list):
    # d_g[n] = 1 + max(d_l[i], if d[n] > d_l[i], i = [0, n - 1])
    # d_l[n] = 1 + max(d_g[i], if d[n] < d_g[i], i = [0, n - 1])

    n = len(number_list)
    real_list = generate_real_part_list(number_list)

    d_l = [1 for x in range(n)]
    d_g = [1 for x in range(n)]
    index_l = [-1 for x in range(n)]
    index_g = [-1 for x in range(n)]

    general_max = 1, False  # tuple[last_index, "greater"]
    for i in range(1, n):
        # "a[j] < a[i]" (greater)
        maxim = 0
        for j in range(i):
            if real_list[j] < real_list[i]:
                if d_l[j] > maxim:
                    maxim = d_l[j]
                    index_g[i] = j
        d_g[i] = 1 + maxim
        if d_g[i] > general_max[0]:
            general_max = i, True

        # "a[j] > a[i]" (lower)
        maxim = 0
        for j in range(i):
            if real_list[j] > real_list[i]:
                if d_g[j] > maxim:
                    maxim = d_g[j]
                    index_l[i] = j
        d_l[i] = 1 + maxim
        if d_l[i] > general_max[0]:
            general_max = i, False

    index_list = [general_max]  # tuple[index, "greater"]
    while index_list[len(index_list) - 1][0] != -1:
        last_item = index_list[len(index_list) - 1]
        if last_item[1]:  # if current is greater
            index_list.append( (index_l[last_item[0]], False) )  # append the index of the lower previous number
        else:
            index_list.append( (index_g[last_item[0]], True) )  # append the index of the greater previous number
    index_list.pop()
    index_list.reverse()
    return [complex_to_str(number_list[index_list[i][0]]) for i in range(len(index_list))]


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#
def print_menu():
    print("\n1. Read a list of complex numbers"
          "\n2. Print current list"
          "\n3. Find subarray / subsequence from the list with some properties"
          "\n4. Exit")


def print_option3_submenu():
    print("a. Longest subarray of numbers where each number's modulus is in the [0, 10] range")
    print("b. Longest alternating subsequence, when considering each number's real part")


def user_option() -> int:
    print_menu()
    user_input = input(">>>").strip()
    if user_input == '1':
        return 1
    elif user_input == '2':
        return 2
    elif user_input == '3':
        print_option3_submenu()
        submenu_user_input = input(">>>").strip()
        if submenu_user_input == 'a':
            return 31
        elif submenu_user_input == 'b':
            return 32
        else:
            return -1
    elif user_input == '4':
        print("Bye!")
        return 4
    else:
        return -1


def read_list() -> list:
    print("Enter the number of elements of the list:")
    n = int(input("n = ").strip())
    new_list = []
    for i in range(n):
        crt_number_str = input()
        crt_number = str_to_complex(crt_number_str)
        new_list.append(crt_number)
    return new_list


def print_current_list(crt_list: list):
    for i in range(len(crt_list)):
        print(complex_to_str(crt_list[i]))


if __name__ == "__main__":
    numbers_list = create_initial_list()
    while True:
        option = user_option()
        if option == 1:
            numbers_list = read_list()
        elif option == 2:
            print_current_list(numbers_list)
        elif option == 31:
            length, result_list = naive_pb_5(numbers_list)
            print("Length:", length)
            print(*result_list)
        elif option == 32:
            result_list = dynamic_pb_12(numbers_list)
            print("Length:", len(result_list))
            print(*result_list)
        elif option == 4:
            break
        else:
            print("Error!")

# TODO modify functions for list like the functions for dict
