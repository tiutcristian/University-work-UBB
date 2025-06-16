import pickle
from pathlib import Path

from src.domain.idobject import IdObject
from src.repository.memory_repository import MemoryRepository


class BinaryFileRepository(MemoryRepository):
    def __init__(self, path_to_file: str):
        super().__init__()
        self.__path = Path(__file__).parent / path_to_file
        self.update_data(self.__get_file_content())

    def __get_file_content(self):
        f = self.__path.open("rb")
        content = pickle.load(f)
        f.close()
        return content

    def __print_content_to_file(self):
        f = self.__path.open("wb")
        pickle.dump(self.get_data(), f)
        f.close()

    def add(self, object: IdObject):
        super().add(object)
        self.__print_content_to_file()

    def remove(self, _id: int):
        super().remove(_id)
        self.__print_content_to_file()

    def update(self, _id: int, object: IdObject):
        super().update(_id, object)
        self.__print_content_to_file()
