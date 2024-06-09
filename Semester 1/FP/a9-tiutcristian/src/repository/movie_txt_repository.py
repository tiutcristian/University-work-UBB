from pathlib import Path

from src.domain.idobject import IdObject
from src.domain.movie import Movie
from src.repository.memory_repository import MemoryRepository


class MovieTextFileRepository(MemoryRepository):
    def __init__(self, path_to_file: str):
        super().__init__()
        self.__path = Path(__file__).parent / path_to_file
        self.update_data(self.__get_file_content())

    def __get_file_content(self):
        f = self.__path.open("r")
        content = self.__convert_str_to_movies(f.read())
        f.close()
        return content

    def __print_content_to_file(self):
        f = self.__path.open("w")
        f.write(self.__convert_movies_to_str(super().get_data()))
        f.close()

    def add(self, movie: Movie):
        super().add(movie)
        self.__print_content_to_file()

    def remove(self, _id: int):
        super().remove(_id)
        self.__print_content_to_file()

    def update(self, _id: int, object: IdObject):
        super().update(_id, object)
        self.__print_content_to_file()

    @staticmethod
    def __convert_movies_to_str(movies: dict) -> str:
        new_str = ''
        for m in movies.values():
            new_str += (
                str(m.id) + ',' +
                m.title + ',' +
                m.description + ',' +
                m.genre + '\n'
            )
        return new_str

    @staticmethod
    def __convert_str_to_movies(string: str) -> dict:
        new_dict = {}
        movies = string.split("\n")
        for m_str in movies[:-1]:
            m_list = m_str.split(',')
            _id = int(m_list[0])
            title = m_list[1]
            description = m_list[2]
            genre = m_list[3]
            new_dict[_id] = Movie(_id, title, description, genre)
        return new_dict
