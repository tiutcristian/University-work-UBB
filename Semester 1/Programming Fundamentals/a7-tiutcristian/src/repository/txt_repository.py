from pathlib import Path
from .repository import Repository
from ..domain import Book


class TextFileRepository(Repository):
    def __init__(self):
        super().__init__()
        print("\nYou are reading from and writing to text file repository.")
        self.__path = Path(__file__).parent / "repository.txt"
        books_imported_from_file = self.__convert_str_to_books(self.__get_file_content())
        super().update_history(books_imported_from_file)

    def __get_file_content(self):
        f = self.__path.open("r")
        content = f.read()
        f.close()
        return content

    def __print_content_to_file(self, content: str):
        f = self.__path.open("w")
        f.write(content)
        f.close()

    def update_history(self, curr_list):
        super().update_history(curr_list)
        content = self.__convert_books_to_str(curr_list)
        self.__print_content_to_file(content)

    def undo_lpo(self):
        super().undo_lpo()
        content = self.__convert_books_to_str(self.get_curr_list())
        self.__print_content_to_file(content)

    @staticmethod
    def __convert_books_to_str(books: list) -> str:
        new_str = ""
        for book in books:
            new_str = new_str + (f"{book.get_isbn()}\n"
                                 f"{book.get_author()}\n"
                                 f"{book.get_title()}\n")
        return new_str

    @staticmethod
    def __convert_str_to_books(string: str) -> list:
        new_list = []
        words = string.split("\n")
        n = len(words)
        n -= n % 3  # because we also have \n after the last attribute in the file (error prevention)
        i = 0
        while i in range(n):
            curr_isbn = words[i]
            i += 1
            curr_author = words[i]
            i += 1
            curr_title = words[i]
            i += 1
            new_book = Book(curr_isbn, curr_author, curr_title)
            new_list.append(new_book)
        return new_list
