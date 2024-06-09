class IdObject:
    def __init__(self, _id: int):
        if not isinstance(_id, int):
            raise IdError("Id cannot be non-integer.")
        self.__id = _id

    @property
    def id(self):
        return self.__id


class IdError(Exception):
    def __init__(self, message):
        self.__message = message

    def get_message(self):
        return self.__message

    def __str__(self):
        return self.__message
