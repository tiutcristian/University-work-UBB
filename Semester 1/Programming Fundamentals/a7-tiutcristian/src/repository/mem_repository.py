from .repository import Repository
from src.domain import Book


class MemoryRepository(Repository):
    def __init__(self):
        super().__init__()
        self.create_initial_entries()
        print("\nYou are reading from and writing to memory repository."
              "\n!!WARNING!! All current data will be wiped out at the end of the execution."
              "\nFor persisting books lists switch to other type of repository from the settings.properties file.")

    def create_initial_entries(self):
        initial_list = [
            Book("initial_mem_isbn_1", "initial_mem_author_1", "initial_mem_title_1"),
            Book("initial_mem_isbn_2", "initial_mem_author_2", "initial_mem_title_2"),
            Book("initial_mem_isbn_3", "initial_mem_author_3", "initial_mem_title_3"),
            Book("initial_mem_isbn_4", "initial_mem_author_4", "initial_mem_title_4"),
            Book("initial_mem_isbn_5", "initial_mem_author_5", "initial_mem_title_5"),
            Book("initial_mem_isbn_6", "initial_mem_author_6", "initial_mem_title_6"),
            Book("initial_mem_isbn_7", "initial_mem_author_7", "initial_mem_title_7"),
            Book("initial_mem_isbn_8", "initial_mem_author_8", "initial_mem_title_8"),
            Book("initial_mem_isbn_9", "initial_mem_author_9", "initial_mem_title_9"),
            Book("initial_mem_isbn_10", "initial_mem_author_10", "initial_mem_title_10")
        ]
        self.update_history(initial_list)
