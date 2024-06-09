from src.domain import Book
from src.repository import *
from jproperties import Properties
from pathlib import Path


class Services(object):
    def __init__(self, repo_type):
        self.__repo = repo_type

    @staticmethod
    def get_repo_type():
        """
        Returns the class corresponding to the settings file
        :return: the corresponding class
        """
        path = Path(__file__).parent / "settings.properties"
        configs = Properties()
        with path.open('rb') as config_file:
            configs.load(config_file)
        repo_type = configs.get("Repo_type")[0]
        if repo_type == "MemoryRepository":
            return MemoryRepository()
        elif repo_type == "TextFileRepository":
            return TextFileRepository()
        elif repo_type == "BinaryFileRepository":
            return BinaryFileRepository()
        elif repo_type == "DatabaseRepository":
            return DatabaseRepository()
        elif repo_type == "JSONFileRepository":
            return JSONFileRepository()

    def get_books_list(self):
        """
        Get current books list
        :return: current books list
        """
        curr_list = self.__repo.get_curr_list()
        return curr_list

    def add_book(self, isbn: str, author: str, title: str):
        """
        Add a book
        :param isbn: isbn
        :param author: author
        :param title: title
        """
        new_book = Book(isbn, author, title)
        self.__repo.add_book(new_book)

    def filter(self, word: str):
        """
        Filter the list so that book titles starting with a given word are deleted from the list
        :param word: the given word
        """
        self.__repo.filter(word)

    def undo(self):
        """
        Undo the last performed operation
        """
        self.__repo.undo_lpo()
