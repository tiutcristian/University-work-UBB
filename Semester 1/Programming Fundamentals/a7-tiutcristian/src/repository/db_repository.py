from .repository import Repository
from ..domain import Book
import mysql.connector


class DatabaseRepository(Repository):
    def __init__(self):
        super().__init__()
        print("\nYou are reading from and writing to database repository.")
        self.__db = mysql.connector.connect(
            host="localhost",
            user="root",
            password="",
            database="books_a7"
        )
        self.__db_cursor = self.__db.cursor()
        self.__get_db_content()
        # for i in range(1, 10):
        #     self.add_book(Book(
        #         f"{i} initial isbn",
        #         f"{i} initial author",
        #         f"{i} initial title"
        #     ))

    def undo_lpo(self):
        """
        Undo last performed operation
        """
        super().undo_lpo()
        curr_list = self.get_curr_list()
        self.__update_database(curr_list)

    def add_book(self, book: Book):
        """
        Add a new book to the repository (history + database)
        :param book: the book to be added
        """
        super().add_book(book)
        sql_query = "INSERT INTO books (isbn, author, title) VALUES (%s, %s, %s)"
        values = (book.get_isbn(), book.get_author(), book.get_title())
        self.__db_cursor.execute(sql_query, values)
        self.__db.commit()

    def filter(self, word: str):
        """
        Filters the list so that book titles starting with a given word are deleted from the list
        :param word: the given word
        """
        initial_list = self.get_curr_list()
        sql_query = "DELETE FROM books WHERE SUBSTRING_INDEX(title, ' ', 1) = %s"
        value = (word, )
        self.__db_cursor.execute(sql_query, value)
        self.__db.commit()
        self.__get_db_content()
        final_list = self.get_curr_list()
        if final_list == initial_list:
            self.history.pop()

    def __get_db_content(self):
        """
        Gets the content of the books table in database and pushes the list to the history
        """
        self.__db_cursor.execute("SELECT * FROM books")
        result = self.__db_cursor.fetchall()
        new_list = []
        for x in result:
            new_book = Book(x[0], x[1], x[2])
            new_list.append(new_book)
        self.update_history(new_list)

    def __update_database(self, entries_list: list[Book]):
        """
        Updates the database according to a given list of books
        :param entries_list: list of books
        """
        self.__db_cursor.execute("DELETE FROM books")
        self.__db.commit()
        for entry in entries_list:
            sql_query = "INSERT INTO books (isbn, author, title) VALUES (%s, %s, %s)"
            values = (entry.get_isbn(), entry.get_author(), entry.get_title())
            self.__db_cursor.execute(sql_query, values)
            self.__db.commit()
