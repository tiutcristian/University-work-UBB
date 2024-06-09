import datetime
from src.repository.memory_repository import MemoryRepository
from src.domain.rental import Rental
from src.services.undo_redo_service import Command, Operation, UndoService


class RentalServices:
    def __init__(
            self,
            rental_repo: MemoryRepository,
            movie_repo: MemoryRepository,
            client_repo: MemoryRepository,
            undo_service: UndoService
    ):
        self.__rental_repo = rental_repo
        self.__movie_repo = movie_repo
        self.__client_repo = client_repo
        self.__undo_service = undo_service

    def add(self, rental_id, movie_id, client_id, due_year, due_month, due_day):
        if not self.check_eligible(client_id):
            raise RentalError("Client has unreturned movies that passed their due date")
        if not (movie_id in self.__movie_repo.get_data().keys()):
            raise RentalError("There exists no movie with that ID")
        if not (client_id in self.__client_repo.get_data().keys()):
            raise RentalError("There exists no client with that ID")
        if datetime.date(due_year, due_month, due_day) <= datetime.date.today():
            raise RentalError("Due date is in the past or current day")
        rental = Rental(
            rental_id,
            movie_id,
            client_id,
            datetime.date.today(),  # rented date
            datetime.date(due_year, due_month, due_day),  # due date
            None  # returned date
        )
        self.__rental_repo.add(rental)
        undo_action = Command(self.remove, rental_id)
        redo_action = Command(self.add, rental_id, movie_id, client_id, due_year, due_month, due_day)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)

    def remove(self, rental_id):
        deleted_rental = self.__rental_repo.find(rental_id)
        self.__rental_repo.remove(rental_id)

        undo_action = Command(self.__rental_repo.add, deleted_rental)
        redo_action = Command(self.remove, rental_id)
        operation = Operation(undo_action, redo_action)
        # self.__undo_service.record_for_undo(operation)
        return operation

    def check_eligible(self, client_id) -> bool:
        for rental in self.get_all_rentals():
            if (rental.client_id == client_id
                    and rental.returned_date is None
                    and rental.due_date < datetime.date.today()):
                return False
        return True

    def return_rental(self, rental_id):
        if self.__rental_repo.find(rental_id) is None:
            raise RentalError("Rental doesn't exist")
        rental = self.__rental_repo.get_by_id(rental_id)
        if not (rental.returned_date is None):
            raise RentalError("Rental already returned")
        rental.set_returned_date(datetime.date.today())

        self.__rental_repo.update(rental_id, rental)

        undo_action = Command(self.unreturn, rental_id)
        redo_action = Command(self.return_rental, rental_id)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)

    def unreturn(self, rental_id):
        rental = self.__rental_repo.get_by_id(rental_id)
        rental.set_returned_date(None)

        self.__rental_repo.update(rental_id, rental)

        undo_action = Command(self.return_rental, rental_id)
        redo_action = Command(self.unreturn, rental_id)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)

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

    def filter_by_client_id(self, client_id):
        new_dict = {}
        for r in self.get_all_rentals():
            if r.client_id == client_id:
                new_dict[r.id] = r
        return new_dict

    def filter_by_movie_id(self, movie_id):
        new_dict = {}
        for r in self.get_all_rentals():
            if r.movie_id == movie_id:
                new_dict[r.id] = r
        return new_dict


class RentalError(Exception):
    pass
