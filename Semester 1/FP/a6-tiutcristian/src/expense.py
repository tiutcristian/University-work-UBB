def get_day(expense: dict):
    return expense["day"]


def get_amount(expense: dict):
    return expense["amount"]


def get_type(expense: dict):
    return expense["type"]


def create_expense(day: int, amount: int, expense_type: str):
    return {
        "day": day,
        "amount": amount,
        "type": expense_type
    }
