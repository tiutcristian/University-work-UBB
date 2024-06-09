from src.domain.idobject import IdObject


class Movie(IdObject):
    def __init__(self, _id: int, title: str, description: str, genre: str):
        super().__init__(_id)
        self.__title = title
        self.__description = description
        self.__genre = genre

    def __str__(self):
        return (f"id = {self.id},"
                f"title = {self.__title},"
                f"description = {self.__description},"
                f"genre = {self.__genre}")

    def __repr__(self):
        return self.__str__()

    @property
    def id(self):
        return super().id

    @property
    def title(self):
        return self.__title

    @property
    def description(self):
        return self.__description

    @property
    def genre(self):
        return self.__genre

    def search(self, string: str) -> bool:
        if (string in str(self.id) or string.lower() in self.__title.lower() or
                string.lower() in self.__description.lower() or string.lower() in self.__genre.lower()):
            return True
        return False


def generate_movies(n: int) -> list:
    _id = 100
    movie_list = []
    for i in range(n):
        title = "Movie title " + str(i)
        description = "Movie description " + str(i)
        genre = "Movie genre " + str(i)
        movie_list.append(Movie(_id + i, title, description, genre))
    return movie_list
