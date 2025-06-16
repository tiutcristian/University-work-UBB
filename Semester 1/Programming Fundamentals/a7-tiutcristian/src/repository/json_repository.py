import json
from pathlib import Path
from .repository import Repository
from ..domain import Book


class JSONFileRepository(Repository):
    def __init__(self):
        super().__init__()
        print("\nYou are reading from and writing to JSON file repository.")
        self.__path = Path(__file__).parent / "repository.json"
        books_imported_from_file = self.__get_file_content()
        super().update_history(books_imported_from_file)

    def __get_file_content(self):
        f = self.__path.open("r")
        dict_list = json.load(f)
        f.close()
        return self.dict_to_books(dict_list)

    def __print_content_to_file(self, books_list: list):
        f = self.__path.open("w")
        json_object = json.dumps(self.books_to_dict(books_list), indent=4)
        f.write(json_object)
        f.close()

    def update_history(self, curr_list: list):
        super().update_history(curr_list)
        self.__print_content_to_file(curr_list)

    def undo_lpo(self):
        super().undo_lpo()
        self.__print_content_to_file(self.get_curr_list())

    @staticmethod
    def books_to_dict(books_list: list) -> list:
        dict_list = []
        for book in books_list:
            new_dict = {
                "isbn": book.get_isbn(),
                "author": book.get_author(),
                "title": book.get_title()
            }
            dict_list.append(new_dict)
        return dict_list

    @staticmethod
    def dict_to_books(dict_list: list) -> list:
        books_list = []
        for curr_dict in dict_list:
            new_book = Book(
                curr_dict["isbn"],
                curr_dict["author"],
                curr_dict["title"]
            )
            books_list.append(new_book)
        return books_list