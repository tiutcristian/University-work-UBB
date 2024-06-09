from src.services.services import Gameplay, GameOver


class ConsoleUI:
    def __init__(self, services: Gameplay):
        print("New console UI instance created")
        self.__serv = services

    def start_ui(self):
        print("UI started")
        while True:
            try:
                self.print_positions()
                self.print_board()

                if self.__serv.active_player == 1:
                    print("Active player: physical player")
                    self.get_user_input()
                else:
                    print("Active player: computer")
                    self.__serv.handle_computer_turn()

                try:
                    self.__serv.switch_player()
                except GameOver as go:
                    print(go)
                    break

            except Exception as e:
                print(e)

    def print_board(self):
        print(self.__serv.get_board_str())

    def print_positions(self):
        print(self.__serv.get_positions_str())

    def get_user_input(self):
        """
        There are 4 types of user input:
        - place a new piece (on an empty place)
        - move a piece (to an empty position on the same segment
            if player has more than 3 pieces on the board)
        - remove a piece of the other player when new morris is created (that is not in
            morris and if all pieces are in morris then player can remove any piece)
        - "jump" a piece (to an empty position if player only has 3 pieces)
        """
        phase = self.__serv.get_phase_of_active_player()
        if phase == Gameplay.PLACEMENT_PHASE:
            pos = self.get_pos_from_user("Enter position to place piece: ")
            self.__serv.place(pos)
            self.check_and_handle_morris_created(pos)
        elif phase == Gameplay.MOVING_PHASE:
            src_pos = self.get_pos_from_user("Enter position of piece to move: ")
            dest_pos = self.get_pos_from_user("Enter position where to move: ")
            self.__serv.move(src_pos, dest_pos)
            self.check_and_handle_morris_created(dest_pos)
        elif phase == Gameplay.JUMPING_PHASE:
            src_pos = self.get_pos_from_user("Enter position of piece to be jumped: ")
            dest_pos = self.get_pos_from_user("Enter position where to jump: ")
            self.__serv.jump(src_pos, dest_pos)
            self.check_and_handle_morris_created(dest_pos)

    @staticmethod
    def get_pos_from_user(text: str):
        pos = input(text)
        if not pos.isdigit():
            raise TypeError("Position should be an integer")
        return int(pos) - 1

    def check_and_handle_morris_created(self, pos: int):
        if self.__serv.is_pos_in_morris(pos):
            print("New morris created.")
            was_removed = False
            while not was_removed:
                pos_rm = self.get_pos_from_user("Enter position of piece to remove: ")
                was_removed = self.__serv.remove(pos_rm)
                if not was_removed:
                    print("Piece was not removed. Invalid position provided.")


