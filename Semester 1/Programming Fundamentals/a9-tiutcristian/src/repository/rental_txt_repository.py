from datetime import datetime

from src.domain.idobject import IdObject
from src.domain.rental import Rental
from src.repository.memory_repository import MemoryRepository
from pathlib import Path


class RentalTextFileRepository(MemoryRepository):
    def __init__(self, path_to_file: str):
        super().__init__()
        self.__path = Path(__file__).parent / path_to_file
        self.update_data(self.__get_file_content())

    def __get_file_content(self):
        f = self.__path.open("r")
        content = self.__convert_str_to_rentals(f.read())
        f.close()
        return content

    def __print_content_to_file(self):
        f = self.__path.open("w")
        f.write(self.__convert_rentals_to_str(super().get_data()))
        f.close()

    def add(self, rental: Rental):
        super().add(rental)
        self.__print_content_to_file()

    def remove(self, _id: int):
        super().remove(_id)
        self.__print_content_to_file()

    def update(self, _id: int, object: IdObject):
        super().update(_id, object)
        self.__print_content_to_file()

    @staticmethod
    def __convert_rentals_to_str(rentals: dict) -> str:
        new_str = ''
        for r in rentals.values():
            new_str += (
                str(r.id) + ',' +
                str(r.movie_id) + ',' +
                str(r.client_id) + ',' +
                str(r.rented_date) + ',' +
                str(r.due_date) + ',' +
                str(r.returned_date) + '\n'
            )
        return new_str

    @staticmethod
    def __convert_str_to_rentals(string: str) -> dict:
        new_dict = {}
        rentals = string.split("\n")
        for r_str in rentals[:-1]:
            r_list = r_str.split(',')
            _id = int(r_list[0])
            movie_id = int(r_list[1])
            client_id = int(r_list[2])
            rented_date = datetime.strptime(r_list[3], '%Y-%m-%d').date()
            due_date = datetime.strptime(r_list[4], '%Y-%m-%d').date()
            returned_date = None if r_list[5] == 'None' else datetime.strptime(r_list[5], '%Y-%m-%d').date()
            new_dict[_id] = Rental(_id, movie_id, client_id, rented_date, due_date, returned_date)
        return new_dict
