from src.repository.repository import Repository
from src.domain.client import Client


class ClientServices:
    def __init__(self, client_repo: Repository):
        self.__client_repo = client_repo

    def add(self, _id: int, name: str):
        """
        Creates a new client with provided details and adds it to the repository
        :param _id: client id
        :param name: client name
        """
        new_client = Client(_id, name)
        self.__client_repo.add(new_client)

    def delete(self, _id: int):
        """
        Delete client by id
        :param _id: client id
        """
        self.__client_repo.remove(_id)

    def update(self, _id: int, name: str):
        """
        Updates client based on provided details
        :param _id: client id
        :param name: new name
        """
        self.__client_repo.update(_id, Client(_id, name))

    def get_clients(self):
        data = self.__client_repo.get_data()
        return data

    def search(self, user_input: str):
        clients = self.get_clients().values()
        found_clients = []
        for c in clients:
            if c.search(user_input):
                found_clients.append(c)
        return found_clients
