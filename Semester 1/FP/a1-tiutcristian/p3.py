def is_leap(n: int) -> bool:
    if n % 400 == 0:
        return True
    elif n % 100 == 0:
        return False
    elif n % 4 == 0:
        return True
    else:
        return False


def entire_years(birth_year: int, curr_year: int) -> int:
    total = 0
    for year in range(birth_year + 1, curr_year):
        if is_leap(year):
            total += 366
        else:
            total += 365
    return total


def entire_months(birth_month: int, birth_year: int, curr_month: int, curr_year: int) -> int:
    total = 0

    # birth year
    no_of_days_in_month = [0, 31, 29 if is_leap(birth_year) else 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    for month in range(birth_month + 1, 13):
        total += no_of_days_in_month[month]

    # current year
    no_of_days_in_month[2] = 29 if is_leap(curr_year) else 28
    for month in range(1, curr_month):
        total += no_of_days_in_month[month]

    return total


def separate_days_birth_year(birth_year: int, birth_month: int, birth_day: int) -> int:
    no_of_days_in_month = [0, 31, 29 if is_leap(birth_year) else 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    return no_of_days_in_month[birth_month] - birth_day + 1


# MAIN ------------------------------------------------
# user input - current date
curr_year = int(input("Enter current year: "))
curr_month = int(input("Enter current month: "))
curr_day = int(input("Enter current day: "))

# user input - birth date
birth_year = int(input("Enter birth year: "))
birth_month = int(input("Enter birth month: "))
birth_day = int(input("Enter birth day: "))

total_days = 0
total_days += entire_years(birth_year, curr_year)
total_days += entire_months(birth_month, birth_year, curr_month, curr_year)
total_days += separate_days_birth_year(birth_year, birth_month, birth_day)
total_days += curr_day  # separate days in current month

print("Total number of days: ", total_days)