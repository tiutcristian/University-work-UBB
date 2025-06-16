from src.domain import Book


class Repository(object):
    def __init__(self):
        self.history = []

    def get_curr_list(self) -> list:
        if self.get_history_length() > 0:
            return self.history[-1].copy()
        return []

    def update_history(self, new_list: list):
        self.history.append(new_list)

    def undo_lpo(self):
        if self.get_history_length() == 1:
            raise ValueError("No more undos")
        self.history.pop()

    def get_history_length(self) -> int:
        return len(self.history)

    def add_book(self, book: Book):
        """
        Adds a new book to the repository
        :param book: the book to be added
        """
        if self.check_unique_isbn(book.get_isbn()):
            curr_list = self.get_curr_list()
            curr_list.append(book)
            self.update_history(curr_list)
        else:
            raise ValueError("ISBN already exists")

    def filter(self, word: str):
        """
        Filters the list so that book titles starting with a given word are deleted from the list
        :param word: the given word
        """
        curr_list = self.get_curr_list()
        new_list = []
        for book in curr_list:
            curr_title_words = book.get_title().split()
            if curr_title_words[0].lower() != word.lower():
                new_list.append(book)
        if new_list != curr_list:
            self.update_history(new_list)

    def check_unique_isbn(self, isbn: str) -> bool:
        """
        Check if the isbn is unique or not
        :param isbn: given isbn
        :return: true if it's unique, false otherwise
        """
        curr_list = self.get_curr_list()
        for book in curr_list:
            if isbn.lower() == book.get_isbn().lower():
                return False
        return True
