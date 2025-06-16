from src.domain.client import Client
from src.domain.idobject import IdObject
from src.repository.memory_repository import MemoryRepository
from pathlib import Path


class ClientTextFileRepository(MemoryRepository):
    def __init__(self, path_to_file: str):
        super().__init__()
        self.__path = Path(__file__).parent / path_to_file
        self.update_data(self.__get_file_content())

    def __get_file_content(self):
        f = self.__path.open("r")
        content = self.__convert_str_to_clients(f.read())
        f.close()
        return content

    def __print_content_to_file(self):
        f = self.__path.open("w")
        f.write(self.__convert_clients_to_str(super().get_data()))
        f.close()

    def add(self, client: Client):
        super().add(client)
        self.__print_content_to_file()

    def remove(self, _id: int):
        super().remove(_id)
        self.__print_content_to_file()

    def update(self, _id: int, object: IdObject):
        super().update(_id, object)
        self.__print_content_to_file()

    @staticmethod
    def __convert_clients_to_str(clients: dict) -> str:
        new_str = ''
        for c in clients.values():
            new_str += str(c.id) + ',' + c.name + '\n'
        return new_str

    @staticmethod
    def __convert_str_to_clients(string: str) -> dict:
        new_dict = {}
        clients = string.split("\n")
        for c_str in clients[:-1]:
            c_list = c_str.split(',')
            _id = int(c_list[0])
            name = c_list[1]
            new_dict[_id] = Client(_id, name)
        return new_dict
