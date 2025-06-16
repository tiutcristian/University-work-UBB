from src.repository.memory_repository import MemoryRepository
from src.domain.movie import Movie
from src.services.undo_redo_service import Command, Operation, UndoService, CascadedOperation
from src.services.rental_services import RentalServices


class MovieServices:
    def __init__(self, movie_repo: MemoryRepository, undo_service: UndoService, rental_service: RentalServices):
        self.__rental_service = rental_service
        self.__undo_service = undo_service
        self.__movie_repo = movie_repo

    def add(self, _id: int, title: str, description: str, genre: str):
        """
        Creates a new movie with provided details and adds it to the repository
        :param _id: movie id
        :param title: movie title
        :param description: movie description
        :param genre: movie genre
        """
        new_movie = Movie(_id, title, description, genre)
        self.__movie_repo.add(new_movie)

        undo_action = Command(self.delete, _id)
        redo_action = Command(self.add, _id, title, description, genre)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)

    def delete(self, _id: int):
        """
        Deletes movie by id
        :param _id: movie id
        """
        movie_to_delete = self.__movie_repo.get_by_id(_id)
        title = movie_to_delete.title
        description = movie_to_delete.description
        genre = movie_to_delete.genre

        undo_action = Command(self.add, _id, title, description, genre)
        redo_action = Command(self.delete, _id)
        movie_operation = Operation(undo_action, redo_action)
        cascaded_ops = [movie_operation]
        rentals = self.__rental_service.filter_by_movie_id(_id)
        for r in rentals.values():
            rental_operation = self.__rental_service.remove(r.id)
            cascaded_ops.append(rental_operation)
        self.__undo_service.record_for_undo(CascadedOperation(cascaded_ops))

        self.__movie_repo.remove(_id)

    def update(self, _id: int, title: str, description: str, genre: str):
        """
        Updates movie based on provided details
        :param _id: movie id
        :param title: new title
        :param description: new description
        :param genre: new genre
        """
        movie_to_update = self.__movie_repo.get_by_id(_id)
        old_title = movie_to_update.title
        old_description = movie_to_update.description
        old_genre = movie_to_update.genre

        undo_action = Command(self.update, _id, old_title, old_description, old_genre)
        redo_action = Command(self.update, _id, title, description, genre)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)

        self.__movie_repo.update(_id, Movie(_id, title, description, genre))

    def get_movies(self):
        data = self.__movie_repo.get_data()
        return data.values()

    def search(self, user_input: str):
        movies = self.get_movies()
        found_movies = []
        for m in movies:
            if m.search(user_input):
                found_movies.append(m)
        return found_movies
