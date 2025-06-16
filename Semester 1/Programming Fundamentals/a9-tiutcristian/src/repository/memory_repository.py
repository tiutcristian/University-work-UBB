from src.domain.idobject import IdObject


class MemoryRepository:
    def __init__(self):
        self.__data = {}

    def update_data(self, new_data: dict):
        self.__data = new_data

    def add(self, object: IdObject):
        """
        Adds a new IdObject to the repository
        :param object: IdObject
        """
        if not isinstance(object, IdObject):
            raise TypeError("Can only add IdObject instances")
        if object.id in self.__data.keys():
            raise RepoError("ID already exists")
        self.__data[object.id] = object

    def remove(self, _id: int):
        """
        Removes object by id
        :param _id: object id
        :return: removed object
        """
        if self.find(_id) is None:
            raise RepoError("Object doesn't exist.")
        return self.__data.pop(_id)

    def find(self, _id: int) -> IdObject:
        return self.__data[_id] if _id in self.__data.keys() else None

    def get_data(self) -> dict[IdObject]:
        return self.__data

    def update(self, _id: int, object: IdObject):
        """
        Updates object by id
        :param _id: id of object to be updated
        :param object: new object to be assigned to given id
        """
        if self.find(_id) is None:
            raise RepoError("Object doesn't exist.")
        self.__data[_id] = object

    def get_by_id(self, _id: int):
        if self.find(_id) is None:
            raise RepoError("Object doesn't exist.")
        return self.__data[_id]


class RepoError(Exception):
    pass
