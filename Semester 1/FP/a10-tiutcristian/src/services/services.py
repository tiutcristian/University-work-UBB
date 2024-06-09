import random

from src.domain.board import Board


class Gameplay:
    PLACEMENT_PHASE = 0
    MOVING_PHASE = 1
    JUMPING_PHASE = 2
    LOST = 3

    def __init__(self, board: Board):
        self.__pieces_placed = {
            Board.PHYSICAL_PLAYER: 0,
            Board.COMPUTER_PLAYER: 0
        }
        self.__pieces_on_board = {
            Board.PHYSICAL_PLAYER: 0,
            Board.COMPUTER_PLAYER: 0
        }
        self.__phase = {
            Board.PHYSICAL_PLAYER: Gameplay.PLACEMENT_PHASE,
            Board.COMPUTER_PLAYER: Gameplay.PLACEMENT_PHASE
        }
        self.__board = board
        self.__active_player = Board.PHYSICAL_PLAYER

    @property
    def active_player(self):
        """
        Returns the active player
        :return: active player
        """
        return self.__active_player

    @property
    def passive_player(self):
        """
        Returns the passive player
        :return: passive player
        """
        if self.active_player == Board.PHYSICAL_PLAYER:
            return Board.COMPUTER_PLAYER
        return Board.PHYSICAL_PLAYER

    def change_active_player(self):
        """
        Changes the active player
        """
        if self.__active_player == Board.PHYSICAL_PLAYER:
            self.__active_player = Board.COMPUTER_PLAYER
        else:
            self.__active_player = Board.PHYSICAL_PLAYER

    def get_phase_of_active_player(self):
        """
        Returns the phase of the active player
        :return: phase of the active player
        """
        return self.__phase[self.active_player]

    def update_phase(self, player: int):
        """
        Updates the phase of the given player
        :param player: the player whose phase is updated
        """
        if self.__pieces_placed[player] < 9:
            self.__phase[player] = Gameplay.PLACEMENT_PHASE
        elif self.__pieces_on_board[player] > 3:
            self.__phase[player] = Gameplay.MOVING_PHASE
        elif self.__pieces_on_board[player] > 2:
            self.__phase[player] = Gameplay.JUMPING_PHASE
        else:  # Lost game
            self.__phase[player] = Gameplay.LOST

    def switch_player(self):
        """
        Updates the phase of the players,
        changes the active player,
        and checks if there is a winner
        :raises: GameOver if the game is over
        """
        self.update_phase(self.active_player)
        self.update_phase(self.passive_player)
        self.change_active_player()
        check_winner = self.get_winner()
        if check_winner == Board.PHYSICAL_PLAYER:
            raise GameOver(f"YOU WON!")
        elif check_winner == Board.COMPUTER_PLAYER:
            raise GameOver(f"COMPUTER WON!")

    def get_winner(self):
        """
        Gets the winner if it exists, otherwise, returns None
        :return: the winner if it exists or None otherwise
        """
        if self.__phase[self.active_player] == Gameplay.LOST:
            return self.passive_player
        elif self.__phase[self.passive_player] == Gameplay.LOST:
            return self.active_player
        else:
            return None

    def get_board(self):
        return self.__board.board

    def get_board_str(self) -> str:
        """
        Returns the board string
        :return: the board string
        """
        return str(self.__board)

    @staticmethod
    def get_positions_str():
        """
        Returns the positions string
        :return: positions string
        """
        return Board.POSITIONS_STRING

    def place(self, pos: int):
        """
        Places the active player at the given position,
        increments the number of pieces placed by the active player,
        and increments the number of pieces on the board of the active player
        :param pos: position where the player should be placed
        """
        self.__board.place(pos, self.active_player)
        self.__pieces_placed[self.active_player] += 1
        self.__pieces_on_board[self.active_player] += 1

    def is_pos_in_morris(self, pos: int):
        """
        Checks if the position is in morris
        :param pos: given position
        """
        return self.__board.is_pos_in_morris(pos)

    def remove(self, pos: int):
        """
        Removes the player at the given position
        :param pos: given position
        """
        was_removed = self.__board.remove(pos, self.active_player)
        if was_removed:
            self.__pieces_on_board[self.passive_player] -= 1
        return was_removed

    def jump(self, src_pos: int, dest_pos: int):
        """
        Moves the player from src_pos to dest_pos
        :param src_pos: source position
        :param dest_pos: destination position
        """
        self.__board.jump(src_pos, dest_pos, self.active_player)

    def move(self, src_pos: int, dest_pos: int):
        """
        Moves the player from src_pos to dest_pos
        :param src_pos: source position
        :param dest_pos: destination position
        """
        self.__board.move(src_pos, dest_pos, self.active_player)

    def computer_player_place(self):
        """
        Places the computer player and checks if a new morris is created
        """
        pos = self.generate_pos_to_place()
        self.place(pos)
        self.computer_player_check_and_handle_morris_created(pos)

    def generate_pos_to_place(self):
        """
        Generates a new position to place the computer player
        :return: computed position
        """
        passive_player_2_piece_conf = self.__board.get_positions_completing_a_morris(self.passive_player)
        if len(passive_player_2_piece_conf) > 0:
            return passive_player_2_piece_conf[0][0]

        active_player_2_piece_conf = self.__board.get_positions_completing_a_morris(self.active_player)
        if len(active_player_2_piece_conf) > 0:
            return active_player_2_piece_conf[0][0]

        pos_list = self.__board.get_valid_pos_to_place()
        return pos_list[random.randint(0, len(pos_list) - 1)]

    def computer_player_move(self):
        """
        Moves the computer player from a position to another position
        """
        src_pos, dest_pos = self.generate_pos_to_move()
        self.move(src_pos, dest_pos)
        self.computer_player_check_and_handle_morris_created(dest_pos)

    def generate_pos_to_move(self):
        """
        Generates 2 new positions to move the computer player from and to
        :return:
        """
        valid_pos_to_move = self.__board.get_valid_pos_to_move(self.active_player)

        physical_player_2_piece_conf = self.__board.get_positions_completing_a_morris(Board.PHYSICAL_PLAYER)
        if len(physical_player_2_piece_conf) > 0:
            for pos_tuple in valid_pos_to_move:
                for elem in physical_player_2_piece_conf:
                    if pos_tuple[1] == elem[0] and not pos_tuple[0] in elem[1]:
                        return pos_tuple

        computer_player_2_piece_conf = self.__board.get_positions_completing_a_morris(Board.COMPUTER_PLAYER)
        if len(computer_player_2_piece_conf) > 0:
            for pos_tuple in valid_pos_to_move:
                for elem in computer_player_2_piece_conf:
                    if pos_tuple[1] == elem[0] and not pos_tuple[0] in elem[1]:
                        return pos_tuple

        return valid_pos_to_move[random.randint(0, len(valid_pos_to_move) - 1)]

    def computer_player_jump(self):
        """
        "Jumps" the computer player from a position to another position
        """
        src_pos, dest_pos = self.generate_pos_to_jump()
        self.jump(src_pos, dest_pos)
        self.computer_player_check_and_handle_morris_created(dest_pos)

    def generate_pos_to_jump(self):
        """
        Generates 2 new positions to jump the computer player from and to
        :return:
        """
        valid_pos_to_jump = self.__board.get_valid_pos_to_jump(self.active_player)

        physical_player_2_piece_conf = self.__board.get_positions_completing_a_morris(self.passive_player)
        if len(physical_player_2_piece_conf) > 0:
            for pos_tuple in valid_pos_to_jump:
                for elem in physical_player_2_piece_conf:
                    if pos_tuple[1] == elem[0] and not pos_tuple[0] in elem[1]:
                        return pos_tuple

        computer_player_2_piece_conf = self.__board.get_positions_completing_a_morris(self.active_player)
        if len(computer_player_2_piece_conf) > 0:
            for pos_tuple in valid_pos_to_jump:
                for elem in computer_player_2_piece_conf:
                    if pos_tuple[1] == elem[0] and not pos_tuple[0] in elem[1]:
                        return pos_tuple

        return valid_pos_to_jump[random.randint(0, len(valid_pos_to_jump) - 1)]

    def computer_player_check_and_handle_morris_created(self, dest_pos):
        """
        Checks if a new morris has been created and handles it
        :param dest_pos: destination position
        """
        if self.is_pos_in_morris(dest_pos):
            pos_rm = self.generate_pos_to_remove()
            self.remove(pos_rm)

    def generate_pos_to_remove(self):
        """
        Generates a position to remove
        :return: position to remove
        """
        valid_pos_to_remove = self.__board.get_valid_pos_to_remove(Board.COMPUTER_PLAYER)
        return valid_pos_to_remove[random.randint(0, len(valid_pos_to_remove) - 1)]

    def handle_computer_turn(self):
        phase = self.get_phase_of_active_player()
        if phase == Gameplay.PLACEMENT_PHASE:
            self.computer_player_place()
        elif phase == Gameplay.MOVING_PHASE:
            self.computer_player_move()
        elif phase == Gameplay.JUMPING_PHASE:
            self.computer_player_jump()


class GameOver(Exception):
    pass
