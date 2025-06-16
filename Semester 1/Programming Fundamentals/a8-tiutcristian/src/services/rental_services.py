import datetime
from src.repository.repository import Repository
from src.domain.rental import Rental


class RentalServices:
    def __init__(self, rental_repo: Repository, movie_repo: Repository, client_repo: Repository):
        self.__rental_repo = rental_repo
        self.__movie_repo = movie_repo
        self.__client_repo = client_repo

    def add(self, rental_id, movie_id, client_id, due_year, due_month, due_day):
        if not self.check_eligible(client_id):
            raise RentalError("Client has unreturned movies that passed their due date")
        if not (movie_id in self.__movie_repo.get_data().keys()):
            raise RentalError("There exists no movie with that ID")
        if not (client_id in self.__client_repo.get_data().keys()):
            raise RentalError("There exists no client with that ID")
        if datetime.date(due_year, due_month, due_day) <= datetime.date.today():
            raise RentalError("Due date is in the past or current day")
        if self.is_rented(movie_id):
            raise RentalError("Movie already rented")
        self.__rental_repo.add(
            Rental(
                rental_id,
                movie_id,
                client_id,
                datetime.date.today(),  # rented date
                datetime.date(due_year, due_month, due_day),  # due date
                None # returned date
            )
        )

    def check_eligible(self, client_id) -> bool:
        for rental in self.get_all_rentals():
            if (rental.client_id == client_id
                    and rental.returned_date is None
                    and rental.due_date < datetime.date.today()):
                return False
        return True

    def is_rented(self, movie_id: int) -> bool:
        rentals = self.__rental_repo.get_data().values()
        for r in rentals:
            if r.movie_id == movie_id:
                return True
        return False

    def return_rental(self, rental_id):
        if self.__rental_repo.find(rental_id) is None:
            raise RentalError("Rental doesn't exist")
        rental = self.__rental_repo.get_by_id(rental_id)
        if not (rental.returned_date is None):
            raise RentalError("Rental already returned")
        rental.set_returned_date(datetime.date.today())
        self.__rental_repo.update(rental_id, rental)

    def get_all_rentals(self):
        return self.__rental_repo.get_data().values()

    def no_of_days_movie(self, searched_movie_id: int):
        cnt = 0
        for rental in self.__rental_repo.get_data().values():
            if rental.movie_id == searched_movie_id:
                if rental.returned_date is not None:
                    cnt += (rental.returned_date - rental.rented_date).days
                else:
                    cnt += (datetime.date.today() - rental.rented_date).days
        return cnt

    def most_rented_movies(self):
        data = self.__movie_repo.get_data().values()
        sorted_dict = sorted(data, key=lambda item: self.no_of_days_movie(item.id), reverse=True)
        return sorted_dict

    def no_of_days_client(self, searched_client_id: int):
        cnt = 0
        for rental in self.__rental_repo.get_data().values():
            if rental.client_id == searched_client_id:
                if rental.returned_date is not None:
                    cnt += (rental.returned_date - rental.rented_date).days
                else:
                    cnt += (datetime.date.today() - rental.rented_date).days
        return cnt

    def most_active_clients(self):
        data = self.__client_repo.get_data().values()
        sorted_dict = sorted(data, key=lambda item: self.no_of_days_client(item.id), reverse=True)
        return sorted_dict

    def late_rentals(self):
        data = self.__rental_repo.get_data().values()
        late_rentals_list = []
        for x in data:
            if x.due_date < datetime.date.today() and x.returned_date is None:
                late_rentals_list.append(x)
        return late_rentals_list


class RentalError(Exception):
    pass
