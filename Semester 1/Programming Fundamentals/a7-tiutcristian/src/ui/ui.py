from src.services import Services


class UI(object):
    def __init__(self, run: Services):
        self.__run = run
        self.menu_text = (
            "\nChoose an option:"
            "\n   1. Add a book"
            "\n   2. Display the list of books"
            "\n   3. Filter the list"
            "\n   4. Undo the last operation"
            "\n   5. Quit"
        )

    def display_books(self):
        curr_books_list = self.__run.get_books_list()
        cnt = 0
        for book in curr_books_list:
            cnt += 1
            print(f"Book {cnt}:\n{book}")

    def start(self):
        while True:
            print(self.menu_text)
            try:
                user_input = input(">>>").strip()
                if not user_input.isdigit():
                    raise ValueError("Invalid input")
                else:
                    user_input = int(user_input)
                    if user_input == 1:
                        isbn = input("isbn = ").strip()
                        if not isbn:
                            raise ValueError("ISBN empty")
                        author = input("author = ").strip()
                        if not author:
                            raise ValueError("Author empty")
                        title = input("title = ").strip()
                        if not title:
                            raise ValueError("Title empty")
                        self.__run.add_book(isbn, author, title)
                    elif user_input == 2:
                        self.display_books()
                    elif user_input == 3:
                        word = input("word = ").strip()
                        if not word:
                            raise ValueError("Word empty")
                        self.__run.filter(word)
                    elif user_input == 4:
                        self.__run.undo()
                    elif user_input == 5:
                        print("Goodbye!")
                        break
                    else:
                        raise ValueError("Invalid input")
            except ValueError as ve:
                print(ve)
