import unittest

from src.domain.board import Board
from src.services.services import Gameplay, GameOver


class MyTestCase(unittest.TestCase):
    def setUp(self):
        print("\nSetting up...")
        self.board = Board()
        self.board.place(0, Board.PHYSICAL_PLAYER)      # top left
        self.board.place(22, Board.COMPUTER_PLAYER)     # bottom center
        self.board.place(1, Board.PHYSICAL_PLAYER)      # top center
        self.board.place(19, Board.COMPUTER_PLAYER)     # center-bottom center
        self.board.place(2, Board.PHYSICAL_PLAYER)      # top right

        self.serv = Gameplay(self.board)

    def test_active_player(self):
        print("Testing getting active player...")

        self.serv._Gameplay__active_player = Board.PHYSICAL_PLAYER
        self.assertEqual(self.serv.active_player, Board.PHYSICAL_PLAYER)
        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.assertEqual(self.serv.active_player, Board.COMPUTER_PLAYER)

    def test_passive_player(self):
        print("Testing getting passive player...")

        self.serv._Gameplay__active_player = Board.PHYSICAL_PLAYER
        self.assertEqual(self.serv.passive_player, Board.COMPUTER_PLAYER)
        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.assertEqual(self.serv.passive_player, Board.PHYSICAL_PLAYER)

    def test_change_active_player(self):
        print("Testing changing active player...")

        self.serv._Gameplay__active_player = Board.PHYSICAL_PLAYER
        self.serv.change_active_player()
        self.assertEqual(self.serv._Gameplay__active_player, Board.COMPUTER_PLAYER)

        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.serv.change_active_player()
        self.assertEqual(self.serv._Gameplay__active_player, Board.PHYSICAL_PLAYER)

    def test_get_phase_of_active_player(self):
        print("Testing getting phase of active player...")

        self.serv._Gameplay__phase[self.serv._Gameplay__active_player] = Gameplay.PLACEMENT_PHASE
        self.assertEqual(self.serv.get_phase_of_active_player(), Gameplay.PLACEMENT_PHASE)

        self.serv._Gameplay__phase[self.serv._Gameplay__active_player] = Gameplay.MOVING_PHASE
        self.assertEqual(self.serv.get_phase_of_active_player(), Gameplay.MOVING_PHASE)

        self.serv._Gameplay__phase[self.serv._Gameplay__active_player] = Gameplay.JUMPING_PHASE
        self.assertEqual(self.serv.get_phase_of_active_player(), Gameplay.JUMPING_PHASE)

        self.serv._Gameplay__phase[self.serv._Gameplay__active_player] = Gameplay.LOST
        self.assertEqual(self.serv.get_phase_of_active_player(), Gameplay.LOST)

    def test_update_phase(self):
        print("Testing update phase...")

        self.serv._Gameplay__pieces_placed[Board.COMPUTER_PLAYER] = 8
        self.serv._Gameplay__pieces_on_board[Board.COMPUTER_PLAYER] = 8
        self.serv.update_phase(Board.COMPUTER_PLAYER)
        self.assertEqual(
            self.serv._Gameplay__phase[Board.COMPUTER_PLAYER],
            Gameplay.PLACEMENT_PHASE
        )

        self.serv._Gameplay__pieces_placed[Board.PHYSICAL_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 4
        self.serv.update_phase(Board.PHYSICAL_PLAYER)
        self.assertEqual(
            self.serv._Gameplay__phase[Board.PHYSICAL_PLAYER],
            Gameplay.MOVING_PHASE
        )

        self.serv._Gameplay__pieces_placed[Board.COMPUTER_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.COMPUTER_PLAYER] = 3
        self.serv.update_phase(Board.COMPUTER_PLAYER)
        self.assertEqual(
            self.serv._Gameplay__phase[Board.COMPUTER_PLAYER],
            Gameplay.JUMPING_PHASE
        )

        self.serv._Gameplay__pieces_placed[Board.PHYSICAL_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 2
        self.serv.update_phase(Board.PHYSICAL_PLAYER)
        self.assertEqual(
            self.serv._Gameplay__phase[Board.PHYSICAL_PLAYER],
            Gameplay.LOST
        )

    def test_switch_player(self):
        print("Testing switching player...")

        passed = True
        self.serv._Gameplay__pieces_placed[Board.PHYSICAL_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 2
        self.serv._Gameplay__pieces_placed[Board.COMPUTER_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.COMPUTER_PLAYER] = 9
        try:
            self.serv.switch_player()
        except Exception as e:
            passed = False
            self.assertEqual(e.__str__(), 'COMPUTER WON!')
        self.assertEqual(passed, False)

        passed = True
        self.serv._Gameplay__pieces_placed[Board.PHYSICAL_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 9
        self.serv._Gameplay__pieces_placed[Board.COMPUTER_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.COMPUTER_PLAYER] = 2
        try:
            self.serv.switch_player()
        except Exception as e:
            passed = False
            self.assertEqual(e.__str__(), 'YOU WON!')
        self.assertEqual(passed, False)

        passed = True
        self.serv._Gameplay__pieces_placed[Board.PHYSICAL_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 3
        self.serv._Gameplay__pieces_placed[Board.COMPUTER_PLAYER] = 9
        self.serv._Gameplay__pieces_on_board[Board.COMPUTER_PLAYER] = 3
        try:
            self.serv.switch_player()
        except Exception as e:
            passed = False
        self.assertEqual(passed, True)

    def test_get_winner(self):
        print("Testing getting winner")

        self.serv._Gameplay__active_player = Board.PHYSICAL_PLAYER
        self.serv._Gameplay__phase[Board.PHYSICAL_PLAYER] = Gameplay.LOST
        self.assertEqual(self.serv.get_winner(), Board.COMPUTER_PLAYER)

        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.serv._Gameplay__phase[Board.COMPUTER_PLAYER] = Gameplay.LOST
        self.assertEqual(self.serv.get_winner(), Board.PHYSICAL_PLAYER)

    def test_get_board_str(self):
        print("Testing getting board string...")

        self.assertEqual(
            self.serv.get_board_str(),
            str(self.board)
        )

    def test_place(self):
        print("Testing placing...")

        self.serv._Gameplay__active_player = Board.PHYSICAL_PLAYER

        passed = True
        try:
            self.serv.place(0)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.place(3)
        except Exception:
            passed = False
        self.assertEqual(passed, True)
        self.assertEqual(self.board.board[3], Board.PHYSICAL_PLAYER)

        passed = True
        try:
            self.serv.place(22)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

    def test_remove(self):
        print("Testing removing...")

        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER

        old_pieces = self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 3
        was_removed = self.serv.remove(0)
        self.assertEqual(was_removed, True)
        self.assertEqual(
            old_pieces - 1,
            self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER]
        )

        old_pieces = self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 3
        was_removed = self.serv.remove(20)
        self.assertEqual(was_removed, False)
        self.assertEqual(
            old_pieces,
            self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER]
        )

        old_pieces = self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER] = 3
        was_removed = self.serv.remove(3)
        self.assertEqual(was_removed, False)
        self.assertEqual(
            old_pieces,
            self.serv._Gameplay__pieces_on_board[Board.PHYSICAL_PLAYER]
        )

    def test_move(self):
        print("Testing moving...")

        self.serv._Gameplay__active_player = Board.PHYSICAL_PLAYER

        passed = True
        try:
            self.serv.move(1, 1)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.move(19, 16)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.move(0, 1)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.move(0, 13)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.move(0, 9)
        except Exception:
            passed = False
        self.assertEqual(passed, True)

    def test_jump(self):
        print("Testing jumping...")

        self.serv._Gameplay__active_player = Board.PHYSICAL_PLAYER

        passed = True
        try:
            self.serv.jump(1, 1, )
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.jump(19, 16)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.jump(0, 1)
        except Exception:
            passed = False
        self.assertEqual(passed, False)

        passed = True
        try:
            self.serv.jump(0, 13)
        except Exception:
            passed = False
        self.assertEqual(passed, True)

    def test_computer_player_place(self):
        print("Testing computer player placing logic...")

        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.serv.computer_player_place()
        self.assertEqual(self.board.board[16], Board.COMPUTER_PLAYER)

    def test_generate_pos_to_place(self):
        print("Testing generate pos to place logic...")

        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.assertEqual(self.serv.generate_pos_to_place(), 16)

    def test_computer_player_move(self):
        print("Testing computer player move logic...")

        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.board._Board__board[17] = Board.COMPUTER_PLAYER
        self.serv.computer_player_move()
        self.assertEqual(self.board.board[17], Board.EMPTY)
        self.assertEqual(self.board.board[16], Board.COMPUTER_PLAYER)

    def test_generate_pos_to_move(self):
        print("Testing generate pos to move logic...")
        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        generated_pos = self.serv.generate_pos_to_move()
        self.assertEqual(
            generated_pos in [(19, 16), (19, 18), (19, 20), (22, 21), (22, 23)],
            True
        )

    def test_computer_player_jump(self):
        print("Testing computer player jump logic...")

        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.board._Board__board[8] = Board.COMPUTER_PLAYER
        self.serv.computer_player_jump()
        self.assertEqual(self.board.board[8], Board.EMPTY)
        self.assertEqual(self.board.board[16], Board.COMPUTER_PLAYER)

    def test_generate_pos_to_jump(self):
        print("Testing generate pos to jump logic...")
        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        generated_pos = self.serv.generate_pos_to_jump()
        self.assertEqual(
            generated_pos in (
                [(19, i) for i in ([j for j in range(3, 19)] + [20, 21, 23])] +
                [(22, i) for i in ([j for j in range(3, 19)] + [20, 21, 23])]
            ),
            True
        )

    def test_computer_player_check_and_handle_morris_created(self):
        print("Testing computer player new morris checking & handling...")
        self.serv._Gameplay__active_player = Board.COMPUTER_PLAYER
        self.board._Board__board[16] = Board.COMPUTER_PLAYER
        self.serv.computer_player_check_and_handle_morris_created(19)
        self.assertEqual(
            (
                self.board._Board__board[0] == Board.EMPTY or
                self.board._Board__board[1] == Board.EMPTY or
                self.board._Board__board[2] == Board.EMPTY
            ),
            True
        )

    def test_generate_pos_to_remove(self):
        print("Testing generate pos to remove logic...")
        position = self.serv.generate_pos_to_remove()
        self.assertEqual(
            position in self.board.get_valid_pos_to_remove(Board.COMPUTER_PLAYER),
            True
        )


if __name__ == '__main__':
    unittest.main()
