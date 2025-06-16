class Book(object):
    def __init__(self, isbn: str, author: str, title: str):
        self.__isbn = isbn
        self.__author = author
        self.__title = title

    def __str__(self) -> str:
        return (f"  - isbn: {self.__isbn}\n"
                f"  - author: {self.__author}\n"
                f"  - title: {self.__title}\n")

    def __eq__(self, other) -> bool:
        if isinstance(other, Book):
            self_attr = [self.__isbn, self.__author, self.__title]
            other_attr = [other.__isbn, other.__author, other.__title]
            return self_attr == other_attr

    def get_isbn(self) -> str:
        return self.__isbn

    def get_author(self) -> str:
        return self.__author

    def get_title(self) -> str:
        return self.__title
