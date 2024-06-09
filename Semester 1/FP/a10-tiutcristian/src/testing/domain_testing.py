import unittest
from src.domain.board import Board


class MyTestCase(unittest.TestCase):
    def setUp(self):
        print("\nSetting up...")
        self.board = Board()
        self.board.place(0, Board.PHYSICAL_PLAYER)      # top left
        self.board.place(22, Board.COMPUTER_PLAYER)     # bottom center
        self.board.place(1, Board.PHYSICAL_PLAYER)      # top center
        self.board.place(19, Board.COMPUTER_PLAYER)     # center-bottom center
        self.board.place(2, Board.PHYSICAL_PLAYER)      # top right

    def test_place(self):
        print("Testing placing...")

        passed = True
        try:
            self.board.place(0, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.place(3, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, True)
        self.assertEqual(self.board.board[3], Board.PHYSICAL_PLAYER)

        passed = True
        try:
            self.board.place(22, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

    def test_remove(self):
        print("Testing removing...")

        was_removed = self.board.remove(0, Board.COMPUTER_PLAYER)
        self.assertEqual(was_removed, True)
        self.assertEqual(self.board.board[0], Board.EMPTY)

        was_removed = self.board.remove(20, Board.PHYSICAL_PLAYER)
        self.assertEqual(was_removed, False)
        self.assertEqual(self.board.board[20], Board.EMPTY)

        was_removed = self.board.remove(1, Board.PHYSICAL_PLAYER)
        self.assertEqual(was_removed, False)
        self.assertEqual(self.board.board[1], Board.PHYSICAL_PLAYER)

    def test_is_removal_valid(self):
        print("Testing checking valid removal...")

        self.assertEqual(
            self.board.is_removal_valid(Board.PHYSICAL_PLAYER, 0),
            False
        )

        self.assertEqual(
            self.board.is_removal_valid(Board.PHYSICAL_PLAYER, 3),
            False
        )

        self.assertEqual(
            self.board.is_removal_valid(Board.PHYSICAL_PLAYER, 22),
            True
        )

        self.assertEqual(
            self.board.is_removal_valid(Board.COMPUTER_PLAYER, 2),
            True
        )

    def test_is_pos_in_morris(self):
        print("Testing checking if pos is in morris...")
        self.assertEqual(
            self.board.is_pos_in_morris(1),
            True
        )

        self.assertEqual(
            self.board.is_pos_in_morris(22),
            False
        )

        self.assertEqual(
            self.board.is_pos_in_morris(20),
            False
        )

    def test_move(self):
        print("Testing moving...")

        passed = True
        try:
            self.board.move(1, 1, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.move(19, 16, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.move(0, 1, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.move(0, 13, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.move(0, 9, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, True)
        self.assertEqual(self.board.board[0], Board.EMPTY)
        self.assertEqual(self.board.board[9], Board.PHYSICAL_PLAYER)

    def test_is_move_valid(self):
        print("Testing checking valid move...")
        self.assertEqual(self.board.is_move_valid(1, 1, Board.PHYSICAL_PLAYER),False)
        self.assertEqual(self.board.is_move_valid(19, 16, Board.PHYSICAL_PLAYER), False)
        self.assertEqual(self.board.is_move_valid(0, 1, Board.PHYSICAL_PLAYER), False)
        self.assertEqual(self.board.is_move_valid(0, 13, Board.PHYSICAL_PLAYER), False)
        self.assertEqual(self.board.is_move_valid(0, 9, Board.PHYSICAL_PLAYER), True)

    def test_jump(self):
        print("Testing jumping...")

        passed = True
        try:
            self.board.jump(1, 1, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.jump(19, 16, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.jump(0, 1, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.board.jump(0, 13, Board.PHYSICAL_PLAYER)
        except Exception:
            passed = False
        self.assertEqual(passed, True)
        self.assertEqual(self.board.board[0], Board.EMPTY)
        self.assertEqual(self.board.board[13], Board.PHYSICAL_PLAYER)

    def is_jump_valid(self):
        print("Testing checking valid move...")
        self.assertEqual(self.board.is_jump_valid(1, 1, Board.PHYSICAL_PLAYER), False)
        self.assertEqual(self.board.is_jump_valid(19, 16, Board.PHYSICAL_PLAYER), False)
        self.assertEqual(self.board.is_jump_valid(0, 1, Board.PHYSICAL_PLAYER), False)
        self.assertEqual(self.board.is_jump_valid(0, 13, Board.PHYSICAL_PLAYER), True)

    def test_get_positions_completing_a_morris(self):
        print("Testing getting positions completing a morris \n"
              "        (2 piece configurations)...")

        self.assertEqual(
            self.board.get_positions_completing_a_morris(Board.PHYSICAL_PLAYER),
            []
        )

        self.assertEqual(
            self.board.get_positions_completing_a_morris(Board.COMPUTER_PLAYER),
            [(16, [16, 19, 22])]
        )

    def test_get_valid_pos_to_place(self):
        print("Testing getting valid positions to place a piece...")

        self.assertEqual(
            self.board.get_valid_pos_to_place(),
            [i for i in range(3, 19)] + [20, 21, 23]
        )

    def test_get_valid_pos_to_move(self):
        print("Testing getting valid positions to move a piece...")

        self.assertEqual(
            self.board.get_valid_pos_to_move(Board.PHYSICAL_PLAYER),
            [(0, 9), (1, 4), (2, 14)]
        )

        self.assertEqual(
            self.board.get_valid_pos_to_move(Board.COMPUTER_PLAYER),
            [(19, 16), (19, 18), (19, 20), (22, 21), (22, 23)]
        )

    def test_get_valid_pos_to_jump(self):
        print("Testing getting valid positions to jump...")

        self.assertEqual(
            self.board.get_valid_pos_to_jump(Board.PHYSICAL_PLAYER),
            [(0, i) for i in range(3, 19)] + [(0, i) for i in [20, 21, 23]] +
            [(1, i) for i in range(3, 19)] + [(1, i) for i in [20, 21, 23]] +
            [(2, i) for i in range(3, 19)] + [(2, i) for i in [20, 21, 23]]
        )

        self.assertEqual(
            self.board.get_valid_pos_to_jump(Board.COMPUTER_PLAYER),
            [(19, i) for i in range(3, 19)] + [(19, i) for i in [20, 21, 23]] +
            [(22, i) for i in range(3, 19)] + [(22, i) for i in [20, 21, 23]]
        )

    def test_get_valid_pos_to_remove(self):
        print("Testing getting valid positions to remove...")

        self.assertEqual(
            self.board.get_valid_pos_to_remove(Board.PHYSICAL_PLAYER),
            [19, 22]
        )

        self.assertEqual(
            self.board.get_valid_pos_to_remove(Board.COMPUTER_PLAYER),
            [0, 1, 2]
        )


if __name__ == '__main__':
    unittest.main()
