import math


def sum(n: int) -> float:
    s = 0
    for i in range(1, n+1):
        s += (-1) ** (i % 2 + 1) * 1 / i
    return s


def show_ln2():
    ln2 = math.log(2)
    print(f"\nln(2) = {ln2}\n")
    numbers_set = [1000, 10000, 100000, 1000000, 10000000]
    for n in numbers_set:
        curr_sum = sum(n)
        print(f"sum = {curr_sum} for n between 1 and {n}")
        print(f"dif = {round(curr_sum - ln2, 4)}\n")
    print("\n\n")


def rearranged_sum(p: int, q: int, fact: int):
    s = 0
    for i in range(fact * p):
        s += 1 / (2 * i + 1)
    for i in range(fact * q):
        s -= 1 / (2 * i + 2)
    return s


def show_rearranged_sum(p: int, q: int):
    numbers_set = [1000, 10000, 100000, 1000000]
    for n in numbers_set:
        print(f"sum = {rearranged_sum(p, q, n)} for n = {n}")
    print("\n\n")


# MAIN -----------------------------------------------
menu_text = ("1. Show that series converges to ln2.\n"
             "2. Compute rearranged sum.\n"
             "3. Quit")
while True:
    print(menu_text)
    option = input(">>> ").strip()
    if option == "1":
        show_ln2()
    elif option == "2":
        p = int(input("p = ").strip())
        q = int(input("q = ").strip())
        show_rearranged_sum(p, q)
    elif option == "3":
        print("Bye!")
        break
    else:
        print("Error!")
# ----------------------------------------------------
