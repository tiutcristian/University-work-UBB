# Problem 1 from set 2

def is_leap_year(n: int) -> bool:
    if n % 400 == 0:
        return True
    elif n % 100 == 0:
        return False
    elif n % 4 == 0:
        return True
    else:
        return False


def generate_list_days_counter(leap: bool) -> list:
    return [0, 31, 29 if leap else 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
# I assigned value 0 to the first position of the list to be more convenient to work with indexes


def get_month(day_no: int, days_list: list) -> int:
    month_index = 0
    while day_no >= 0:
        month_index += 1
        day_no -= days_list[month_index]
    return month_index


def get_day(day_no: int, month_cnt: int, days_list: list) -> int:
    for i in range(1, month_cnt):
        day_no -= days_list[i]
    return day_no


# MAIN -------------------------------------------------------
year = int(input("Enter year: "))
days_list = generate_list_days_counter(is_leap_year(year))
day_no = int(input("Enter number of days: "))
month = get_month(day_no, days_list)
day = get_day(day_no, month, days_list)
print(f"Date: {year}.{month}.{day}")