"""
Nr. matricol = 3636
    Pb.1: % 5 + 1 = 2
    Pb.2: % 6 + 1 = 1
    Pb.3: % 4 + 1 = 1
"""


def is_prime(n: int) -> bool:
    if n < 2:
        return False
    elif n == 2:
        return True
    elif n % 2 == 0:
        return False
    else:
        i = 3
        while i * i <= n:
            if n % i == 0:
                return False
            else:
                i += 2
    return True

def read() -> int:
    user_input = input("Enter the number n: ")
    return int(user_input)


n = read()
if is_prime(n - 2):
    print(f"Numbers are: 2 and {n - 2}")
else:
    i = 3
    found = False
    while found == False and i <= n / 2:
        if is_prime(i) and is_prime(n - i):
            found = True
            print(f"Numbers are: {i} and {n - i}")
        else:
            i += 2
    if found == False:
        print("There do not exist such 2 prime numbers.")