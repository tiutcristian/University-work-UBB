"""
Implementation for problem 13:

"""

from lista import creare_lista, included_in, remove_all_occurrences, tipar


def first_requirement():
    print("\nInput first list:")
    lista1 = creare_lista()

    print("\nInput second list:")
    lista2 = creare_lista()

    if included_in(lista1, lista2):
        print("First list is included in the second list")
    else:
        print("First list is NOT included in the second list")


def second_requirement():
    print("\nInput list:")
    lista = creare_lista()

    val = int(input("Enter value to be removed: "))

    remove_all_occurrences(lista, val)

    print("List without the value ", val)
    tipar(lista)


if __name__ == '__main__':

    while True:
        print("\nMenu:")
        print("1. First requirement")
        print("2. Second requirement")
        print("0. Exit")
        option = int(input("Enter option: "))
        if option == 1:
            first_requirement()
        elif option == 2:
            second_requirement()
        elif option == 0:
            print("Exiting...")
            break
        else:
            print("Invalid option")
