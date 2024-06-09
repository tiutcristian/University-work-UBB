from src.repository.memory_repository import MemoryRepository
from src.domain.client import Client
from src.services.rental_services import RentalServices
from src.services.undo_redo_service import Command, Operation, UndoService, CascadedOperation


class ClientServices:
    def __init__(self, client_repo: MemoryRepository, undo_service: UndoService, rental_service: RentalServices):
        self.__undo_service = undo_service
        self.__client_repo = client_repo
        self.__rental_service = rental_service

    def add(self, _id: int, name: str):
        """
        Creates a new client with provided details and adds it to the repository
        :param _id: client id
        :param name: client name
        """
        new_client = Client(_id, name)
        self.__client_repo.add(new_client)

        undo_action = Command(self.delete, _id)
        redo_action = Command(self.add, _id, name)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)

    def delete(self, _id: int):
        """
        Delete client by id
        :param _id: client id
        """
        name = self.__client_repo.get_by_id(_id).name

        undo_action = Command(self.add, _id, name)
        redo_action = Command(self.delete, _id)
        client_operation = Operation(undo_action, redo_action)
        cascaded_ops = [client_operation]
        client_rentals = self.__rental_service.filter_by_client_id(_id)
        for r in client_rentals.values():
            rental_operation = self.__rental_service.remove(r.id)
            cascaded_ops.append(rental_operation)
        self.__undo_service.record_for_undo(CascadedOperation(cascaded_ops))
        self.__client_repo.remove(_id)

    def update(self, _id: int, name: str):
        """
        Updates client based on provided details
        :param _id: client id
        :param name: new name
        """
        old_name = self.__client_repo.get_by_id(_id).name
        self.__client_repo.update(_id, Client(_id, name))

        undo_action = Command(self.update, _id, old_name)
        redo_action = Command(self.update, _id, name)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)

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
