import random
from src.domain.idobject import IdObject


class Client(IdObject):
    def __init__(self, _id: int, name: str):
        super().__init__(_id)
        self.__name = name

    def __str__(self):
        return f"id = {self.id}, name = {self.__name}"

    def __repr__(self):
        return self.__str__()

    @property
    def id(self):
        return super().id

    def search(self, string: str) -> bool:
        if string in str(self.id) or string.lower() in self.__name.lower():
            return True
        return False


def generate_clients(n: int) -> list:
    _id = 100
    last_names = ['Smith', 'Jones', 'Williams', 'Taylor', 'Brown', 'Wilson', 'Davies', 'Evans', 'Thomas', 'Johnson']
    first_names = ["Oliver", "William", "Jack", "Harry", "Leo", "Olivia", "Amelia", "Evelyn", "Grace", "Sophie"]
    result = []
    for i in range(n):
        result.append(Client(_id + i, random.choice(first_names) + " " + random.choice(last_names)))
    return result
