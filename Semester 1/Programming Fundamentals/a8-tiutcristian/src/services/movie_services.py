from src.repository.repository import Repository
from src.domain.movie import Movie


class MovieServices:
    def __init__(self, movie_repo: Repository):
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

    def delete(self, _id: int):
        """
        Deletes movie by id
        :param _id: movie id
        """
        self.__movie_repo.remove(_id)

    def update(self, _id: int, title: str, description: str, genre: str):
        """
        Updates movie based on provided details
        :param _id: movie id
        :param title: new title
        :param description: new description
        :param genre: new genre
        """
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
