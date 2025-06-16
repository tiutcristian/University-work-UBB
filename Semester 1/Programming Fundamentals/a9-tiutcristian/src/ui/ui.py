from src.services.rental_services import RentalServices
from src.services.movie_services import MovieServices
from src.services.client_services import ClientServices
from src.services.undo_redo_service import UndoService


class UIError(Exception):
    pass


class UI(object):
    def __init__(self, rental_serv: RentalServices, movie_serv: MovieServices, client_serv: ClientServices,
                 undo_serv: UndoService):
        self.__rental_serv = rental_serv
        self.__movie_serv = movie_serv
        self.__client_serv = client_serv
        self.__undo_serv = undo_serv
        self.__menu_text = (
            "\nChoose an option:"
            "\n   1. Manage clients"
            "\n   2. Manage movies"
            "\n   3. Manage rentals"
            "\n   4. Generate statistics"
            "\n   5. Undo"
            "\n   6. Redo"
            "\n   7. Quit"
        )

    def __option1(self):  # Manage clients
        print("       1. Add"
              "\n       2. Remove"
              "\n       3. Update"
              "\n       4. List"
              "\n       5. Search")
        user_input = input(">>>").strip()

        if user_input == '1':
            id_str = input("id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            _id = int(id_str)
            name = input("name = ").strip()
            self.__client_serv.add(_id, name)

        elif user_input == '2':
            id_str = input("id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            _id = int(id_str)
            self.__client_serv.delete(_id)

        elif user_input == '3':
            id_str = input("id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            _id = int(id_str)
            new_name = input("new name = ").strip()
            self.__client_serv.update(_id, new_name)

        elif user_input == '4':
            clients = self.__client_serv.get_clients()
            for client in clients.values():
                print(client)

        elif user_input == '5':
            usr_input = input(">>>").strip()
            found_clients = self.__client_serv.search(usr_input)
            for c in found_clients:
                print(c)

        else:
            raise UIError("Invalid input")

    def __option2(self):  # Manage movies
        print("       1. Add"
              "\n       2. Remove"
              "\n       3. Update"
              "\n       4. List"
              "\n       5. Search")
        user_input = input(">>>").strip()

        if user_input == '1':
            id_str = input("id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            _id = int(id_str)
            title = input("title = ").strip()
            description = input("description = ").strip()
            genre = input("genre = ").strip()
            self.__movie_serv.add(_id, title, description, genre)

        elif user_input == '2':
            id_str = input("id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            _id = int(id_str)
            self.__movie_serv.delete(_id)

        elif user_input == '3':
            id_str = input("id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            _id = int(id_str)
            new_title = input("new title = ").strip()
            new_description = input("new description = ").strip()
            new_genre = input("new genre = ").strip()
            self.__movie_serv.update(_id, new_title, new_description, new_genre)

        elif user_input == '4':
            movies = self.__movie_serv.get_movies()
            for movie in movies:
                print(movie)

        elif user_input == '5':
            usr_input = input(">>>").strip()
            found_movies = self.__movie_serv.search(usr_input)
            for m in found_movies:
                print(m)

        else:
            raise UIError("Invalid input")

    def __option3(self):  # Manage rentals
        print("       1. Rent"
              "\n       2. Return"
              "\n       3. Print all rentals")
        user_input = input(">>>").strip()
        if user_input == '1':
            # rent
            id_str = input("rental id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            rental_id = int(id_str)

            id_str = input("client id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            client_id = int(id_str)

            id_str = input("movie id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            movie_id = int(id_str)

            year_str = input("due year = ").strip()
            if not year_str.isdigit():
                raise UIError("Year should be a number")
            due_year = int(year_str)

            month_str = input("due month = ").strip()
            if not month_str.isdigit():
                raise UIError("Month should be a number")
            due_month = int(month_str)

            day_str = input("due day = ").strip()
            if not day_str.isdigit():
                raise UIError("Day should be a number")
            due_day = int(day_str)
            self.__rental_serv.add(rental_id, movie_id, client_id, due_year, due_month, due_day)

        elif user_input == '2':
            id_str = input("rental id = ").strip()
            if not id_str.isdigit():
                raise UIError("ID should be a number")
            rental_id = int(id_str)
            self.__rental_serv.return_rental(rental_id)

        elif user_input == '3':
            for r in self.__rental_serv.get_all_rentals():
                print(r)

        else:
            raise UIError("Invalid input")

    def __option4(self):
        print("       1. Most rented movies"
              "\n       2. Most active clients"
              "\n       3. Late rentals")
        user_input = input(">>>").strip()

        if user_input == '1':
            mrm = self.__rental_serv.most_rented_movies()
            for m in mrm:
                print(m)
        elif user_input == '2':
            mac = self.__rental_serv.most_active_clients()
            for c in mac:
                print(c)
        elif user_input == '3':
            lr = self.__rental_serv.late_rentals()
            for r in lr:
                print(r)
        else:
            raise UIError("Invalid input")

    def start(self):
        while True:
            print(self.__menu_text)
            try:
                user_input = input(">>>").strip()
                if user_input == '1':
                    self.__option1()
                elif user_input == '2':
                    self.__option2()
                elif user_input == '3':
                    self.__option3()
                elif user_input == '4':
                    self.__option4()
                elif user_input == '5':
                    self.__undo_serv.undo()
                elif user_input == '6':
                    self.__undo_serv.redo()
                elif user_input == '7':
                    print("Goodbye!")
                    break
                else:
                    raise UIError("Invalid input")
            except Exception as e:
                print(e)
