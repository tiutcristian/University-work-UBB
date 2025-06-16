from src.domain.idobject import IdObject
from datetime import date, timedelta
from src.domain.movie import generate_movies
from src.domain.client import generate_clients
import random


class Rental(IdObject):
    def __init__(self, _id: int, movie_id: int, client_id: int, rented_date: date, due_date: date, returned_date: date):
        super().__init__(_id)
        self.__movie_id = movie_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        self.__due_date = due_date
        self.__returned_date = returned_date

    def __str__(self):
        return (f"id = {self.id}, "
                f"movie id = {self.__movie_id},"
                f"client id = {self.__client_id},"
                f"rented date = {self.__rented_date},"
                f"due date = {self.__due_date},"
                f"returned date = {self.__returned_date}")

    def __repr__(self):
        return self.__str__()

    @property
    def id(self):
        return super().id

    @property
    def movie_id(self):
        return self.__movie_id

    @property
    def client_id(self):
        return self.__client_id

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def due_date(self):
        return self.__due_date

    @property
    def returned_date(self):
        return self.__returned_date

    def set_returned_date(self, _date: date):
        self.__returned_date = _date


def generate_rentals(n):
    movies = generate_movies(n)
    clients = generate_clients(n)
    _id = 100

    rentals = []
    for i in range(n):
        movie = random.choice(movies)
        client = random.choice(clients)

        rented_date = date.today() + timedelta(days=random.randint(-60, -10))
        due_date = rented_date + timedelta(days=random.randint(5, 20))
        returned_date = random.choice([None, date.today() + timedelta(days=random.randint(-9, 0))])

        rentals.append(Rental(_id + i, movie.id, client.id, rented_date, due_date, returned_date))

    return movies, clients, rentals
