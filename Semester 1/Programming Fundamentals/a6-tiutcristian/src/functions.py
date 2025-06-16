#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print
# statements. Functions here communicate via function parameters, the return statement and raising of exceptions.
#
import expense
from sys import maxsize


def initial_list() -> list[dict]:
    new_list = []
    new_list = add_new_expense(1, 100, "housekeeping", new_list)
    new_list = add_new_expense(2, 200, "food", new_list)
    new_list = add_new_expense(3, 300, "transport", new_list)
    new_list = add_new_expense(4, 400, "clothing", new_list)
    new_list = add_new_expense(5, 500, "internet", new_list)
    new_list = add_new_expense(6, 600, "others", new_list)
    new_list = add_new_expense(7, 700, "housekeeping", new_list)
    new_list = add_new_expense(8, 800, "food", new_list)
    new_list = add_new_expense(9, 900, "transport", new_list)
    new_list = add_new_expense(10, 1000, "clothing", new_list)
    return new_list


def add_new_expense(day: int, amount: int, expense_type: str, expenses_list: list) -> list:
    """
    Add new expense
    :param day: day
    :param amount: amount
    :param expense_type: category
    :param expenses_list: current list
    :return: new list containing the new expense
    """
    categories = [
        "housekeeping",
        "food",
        "transport",
        "clothing",
        "internet",
        "others"
    ]
    if not (1 <= day <= 30):
        raise ValueError("Error! Day should be a number between 1 and 30!")
    elif not expense_type in categories:
        raise ValueError("Error! Expense type is not among specified categories!")
    else:
        new_expense = expense.create_expense(day, amount, expense_type)
        new_list = expenses_list.copy()
        new_list.append(new_expense)
        return new_list


def test_add():
    assert add_new_expense(1, 100, "housekeeping", []) == [
        {
            "day": 1,
            "amount": 100,
            "type": "housekeeping"
        }
    ]
    assert add_new_expense(2, 200, "food", []) == [
        {
            "day": 2,
            "amount": 200,
            "type": "food"
        }
    ]
    assert add_new_expense(3, 300, "transport", []) == [
        {
            "day": 3,
            "amount": 300,
            "type": "transport"
        }
    ]


def remove(start_day: int, end_day: int, expenses_list: list) -> list:
    """
    Remove all expenses from start_day to end_day
    :param start_day: First day to be removed
    :param end_day: Last day to be removed
    :param expenses_list: current list
    :return: new list without the removed expenses
    """
    if not (1 <= start_day <= 30) or not (1 <= end_day <= 30):
        raise ValueError("Error! Day should be a number between 1 and 30!")
    else:
        new_list = []
        for exp in expenses_list:
            if not start_day <= expense.get_day(exp) <= end_day:
                new_list.append(exp)
        return new_list


def test_remove():
    new_list = [
        {
            "day": 1,
            "amount": 100,
            "type": "housekeeping"
        },
        {
            "day": 2,
            "amount": 200,
            "type": "food"
        },
        {
            "day": 3,
            "amount": 300,
            "type": "transport"
        }
    ]
    assert remove(2, 3, new_list) == [
        {
            "day": 1,
            "amount": 100,
            "type": "housekeeping"
        }
    ]
    assert remove(2, 2, new_list) == [
        {
            "day": 1,
            "amount": 100,
            "type": "housekeeping"
        },
        {
            "day": 3,
            "amount": 300,
            "type": "transport"
        }
    ]


def remove_category(expense_type: str, expenses_list: list) -> list:
    """
    Remove all expenses from one category
    :param expense_type: category
    :param expenses_list: current list
    :return: new list without the removed expenses
    """
    categories = [
        "housekeeping",
        "food",
        "transport",
        "clothing",
        "internet",
        "others"
    ]
    if not expense_type in categories:
        raise ValueError("Error! Expense type is not among specified categories!")
    else:
        new_list = []
        for exp in expenses_list:
            if not expense.get_type(exp) == expense_type:
                new_list.append(exp)
        return new_list


def test_remove_category():
    new_list = [
        {
            "day": 1,
            "amount": 100,
            "type": "housekeeping"
        },
        {
            "day": 2,
            "amount": 200,
            "type": "food"
        },
        {
            "day": 3,
            "amount": 300,
            "type": "transport"
        }
    ]
    assert remove_category("housekeeping", new_list) == [
        {
            "day": 2,
            "amount": 200,
            "type": "food"
        },
        {
            "day": 3,
            "amount": 300,
            "type": "transport"
        }
    ]
    assert remove_category("transport", new_list) == [
        {
            "day": 1,
            "amount": 100,
            "type": "housekeeping"
        },
        {
            "day": 2,
            "amount": 200,
            "type": "food"
        }
    ]


def filter_expenses(expenses_list: list, start_value=-1, end_value=-1, expense_type="") -> list:
    """
    Filter expenses by given requirements
    :param expenses_list: current list
    :param start_value: smallest acceptable amount
    :param end_value: largest acceptable amount
    :param expense_type: category
    :return: new list with selected expenses
    """
    categories = [
        "housekeeping",
        "food",
        "transport",
        "clothing",
        "internet",
        "others"
    ]
    if not expense_type == "" and not expense_type in categories:
        raise ValueError("Error! Expense type is not among specified categories!")
    else:
        new_list = []
        for exp in expenses_list:
            if expense_type == "" or expense_type == expense.get_type(exp):
                if start_value <= expense.get_amount(exp) <= (maxsize if end_value == -1 else end_value):
                    new_list.append(exp)
        return new_list


def undo(history: list) -> list:
    """
    Remove last performed operation
    :param history: current history
    :return: history without last list
    """
    if len(history) > 1:
        history.pop()
        return history
    else:
        raise ValueError("No undo left!")


def print_list(expenses_list: list):
    for exp in expenses_list:
        print(exp)
