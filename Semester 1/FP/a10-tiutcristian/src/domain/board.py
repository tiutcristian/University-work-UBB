class Board:
    EMPTY = 0
    PHYSICAL_PLAYER = 1
    COMPUTER_PLAYER = 2
    POSITIONS_STRING = (" 1----------------2----------------3\n"
                        " |                |                |\n"
                        " |     4----------5----------6     |\n"
                        " |     |          |          |     |\n"
                        " |     |     7----8----9     |     |\n"
                        " |     |     |         |     |     |\n"
                        "10----11----12        13----14----15\n"
                        " |     |     |         |     |     |\n"
                        " |     |    16---17---18     |     |\n"
                        " |     |          |          |     |\n"
                        " |    19---------20---------21     |\n"
                        " |                |                |\n"
                        "22---------------23---------------24\n")
    SEGMENTS = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [9, 10, 11],
        [12, 13, 14],
        [15, 16, 17],
        [18, 19, 20],
        [21, 22, 23],
        [0, 9, 21],
        [3, 10, 18],
        [6, 11, 15],
        [1, 4, 7],
        [16, 19, 22],
        [8, 12, 17],
        [5, 13, 20],
        [2, 14, 23]
    ]
    ADJ = [
        [1, 9],             # for 0
        [0, 2, 4],          # for 1
        [1, 14],            # for 2
        [4, 10],            # for 3
        [1, 3, 5, 7],       # for 4
        [4, 13],            # for 5
        [7, 11],            # for 6
        [4, 6, 8],          # for 7
        [7, 12],            # for 8
        [0, 10, 21],        # for 9
        [3, 9, 11, 18],     # for 10
        [6, 10, 15],        # for 11
        [8, 13, 17],        # for 12
        [5, 12, 14, 20],    # for 13
        [2, 13, 23],        # for 14
        [11, 16],           # for 15
        [15, 17, 19],       # for 16
        [12, 16],           # for 17
        [10, 19],           # for 18
        [16, 18, 20, 22],   # for 19
        [13, 19],           # for 20
        [9, 22],            # for 21
        [19, 21, 23],       # for 22
        [14, 22],           # for 23
    ]

    def __init__(self):
        self.__board = [0] * 24

    def __str__(self):
        return (f"{self.__board[0]}----------------{self.__board[1]}----------------{self.__board[2]}\n"
                "|                |                |\n"
                f"|     {self.__board[3]}----------{self.__board[4]}----------{self.__board[5]}     |\n"
                "|     |          |          |     |\n"
                f"|     |     {self.__board[6]}----{self.__board[7]}----{self.__board[8]}     |     |\n"
                "|     |     |         |     |     |\n"
                f"{self.__board[9]}-----{self.__board[10]}-----{self.__board[11]}         {self.__board[12]}-----{self.__board[13]}-----{self.__board[14]}\n"
                "|     |     |         |     |     |\n"
                f"|     |     {self.__board[15]}----{self.__board[16]}----{self.__board[17]}     |     |\n"
                "|     |          |          |     |\n"
                f'|     {self.__board[18]}----------{self.__board[19]}----------{self.__board[20]}     |\n'
                "|                |                |\n"
                f"{self.__board[21]}----------------{self.__board[22]}----------------{self.__board[23]}\n")

    def __repr__(self):
        return self.__str__()

    @property
    def board(self):
        return self.__board

    def place(self, pos: int, player: int):
        """
        Place player on the board according to the given position
        :param pos: given position
        :param player: given player
        :raises ValueError: if position is not empty
        """
        if self.__board[pos] == Board.EMPTY:
            self.__board[pos] = player
        else:
            raise ValueError("pos not empty")

    def remove(self, pos: int, active_player: int) -> bool:
        """
        Remove a piece from the board according to the given position
        :param pos: given position
        :param active_player: active player
        :return: True or false
        """
        if self.is_removal_valid(active_player, pos):
            self.__board[pos] = Board.EMPTY
            return True
        return False

    def is_removal_valid(self, player: int, pos: int):
        """
        Check if a removal is valid
        :param player: active player
        :param pos: position to check
        :return: true/false
        """
        if (
                self.__board[pos] == player or
                self.__board[pos] == Board.EMPTY
        ):
            return False
        elif not self.is_pos_in_morris(pos):
            return True
        else:
            for p in range(0, 24):
                if (
                        self.__board[p] != Board.EMPTY and
                        self.__board[p] != player and
                        not self.is_pos_in_morris(p)
                ):
                    return False
            return True

    def is_pos_in_morris(self, pos: int):
        """
        Check if a position is in a morris
        :param pos: position to check
        :return: true/false
        """
        for seg in Board.SEGMENTS:
            if (
                    pos in seg and
                    self.__board[seg[0]] != Board.EMPTY and
                    self.__board[seg[0]] == self.__board[seg[1]] and
                    self.__board[seg[1]] == self.__board[seg[2]]
            ):
                return True
        return False

    def move(self, src_pos: int, dest_pos: int, player: int):
        """
        Moves the player from src_pos to dest_pos
        :param src_pos: position to move from
        :param dest_pos: position to move to
        :param player: player who played the move
        :raises ValueError: if positions are not adjacent
        """
        if self.is_move_valid(src_pos, dest_pos, player):
            self.jump(src_pos, dest_pos, player)
        else:
            raise ValueError("move not valid")

    def is_move_valid(self, src_pos: int, dest_pos: int, player: int):
        """
        Check if a move is valid
        :param src_pos: source position
        :param dest_pos: destination position
        :param player: player who played the move
        :return: true if the move is valid, false otherwise
        """
        return (
                src_pos != dest_pos and
                self.__board[src_pos] == player and
                self.__board[dest_pos] == Board.EMPTY and
                dest_pos in Board.ADJ[src_pos]
        )

    def jump(self, src_pos: int, dest_pos: int, player: int):
        """
        Jumps given player from src_pos to dest_pos
        :param src_pos: source position
        :param dest_pos: destination position
        :param player: given player
        """
        if self.is_jump_valid(src_pos, dest_pos, player):
            self.__board[src_pos] = Board.EMPTY
            self.place(dest_pos, player)
        else:
            raise ValueError("jump not valid")

    def is_jump_valid(self, src_pos: int, dest_pos: int, player: int):
        """
        Check if a jump is valid
        :param src_pos: source position
        :param dest_pos: destination position
        :param player: given player
        :return: tree/false
        """
        return (
                src_pos != dest_pos and
                self.__board[src_pos] == player and
                self.__board[dest_pos] == Board.EMPTY
        )

    def get_positions_completing_a_morris(self, player: int):
        """
        Get positions in board that complete to a morris of the player
        :param player: get player's positions that complete a morris
        :return: list of positions
        """
        complete_to_morris = []
        for seg in Board.SEGMENTS:
            values = []
            for x in seg:
                values.append(self.__board[x])
            if values == [Board.EMPTY, player, player]:
                complete_to_morris.append((seg[0], seg))
            elif values == [player, Board.EMPTY, player]:
                complete_to_morris.append((seg[1], seg))
            elif values == [player, player, Board.EMPTY]:
                complete_to_morris.append((seg[2], seg))
        return complete_to_morris

    def get_valid_pos_to_place(self):
        """
        Generates a list of valid positions to place
        :return: list of valid positions
        """
        pos_list = []
        for pos in range(24):
            if self.__board[pos] == Board.EMPTY:
                pos_list.append(pos)
        return pos_list

    def get_valid_pos_to_move(self, player: int):
        """
        Get a list of tuples consisting of positions valid to move
        :param player: player making the move
        :return: list[tuple]
        """
        valid_moves_list = []
        for src_pos in range(0, 24):
            for dest_pos in range(0, 24):
                if self.is_move_valid(src_pos, dest_pos, player):
                    valid_moves_list.append((src_pos, dest_pos))
        return valid_moves_list

    def get_valid_pos_to_jump(self, player: int):
        """
        Get a list of tuples consisting of positions valid to jump
        :param player: player making the jump
        :return: list[tuple]
        """
        valid_jumps_list = []
        for src_pos in range(0, 24):
            for dest_pos in range(0, 24):
                if self.is_jump_valid(src_pos, dest_pos, player):
                    valid_jumps_list.append((src_pos, dest_pos))
        return valid_jumps_list

    def get_valid_pos_to_remove(self, player: int):
        """
        Get a list of tuples consisting of positions valid to remove
        :param player: player making the remove
        :return: list[tuple]
        """
        removal_list = []
        for pos in range(24):
            if self.is_removal_valid(player, pos):
                removal_list.append(pos)
        return removal_list
