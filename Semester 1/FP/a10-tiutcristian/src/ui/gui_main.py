from src.ui.gui import *
from src.services.services import Gameplay, GameOver


class GUI:
    GET_POS_TO_PLACE = 0
    GET_POS_TO_MOVE = 1
    GET_POS_TO_MOVE_TO = 2
    GET_POS_TO_JUMP = 3
    GET_POS_TO_JUMP_TO = 4
    GET_POS_TO_REMOVE = 5
    EMPTY_POS_STYLESHEET = (
        "QPushButton{background-color: #3465a4;}\n"
        "QPushButton:hover{background-color: #205190;}"
    )
    HUMAN_PLAYER_STYLESHEET = (
        "QPushButton{background-color: #fff48c;}\n"
        "QPushButton:hover{background-color: #fff7b0;}"
    )
    COMPUTER_PLAYER_STYLESHEET = (
        "QPushButton{background-color: #111;}\n"
        "QPushButton:hover{background-color: #333;}"
    )

    def __init__(self, services: Gameplay):
        # set up stuff from the imported module
        self.__app = QApplication()
        self.__ui = Ui_MainWindow()
        self.__mainwindow = QMainWindow(None)
        self.__ui.setupUi(self.__mainwindow)

        # set up stuff from this class
        self.__serv = services
        self.__buttons = [
            self.__ui.button0, self.__ui.button1, self.__ui.button2, self.__ui.button3,
            self.__ui.button4, self.__ui.button5, self.__ui.button6, self.__ui.button7,
            self.__ui.button8, self.__ui.button9, self.__ui.button10, self.__ui.button11,
            self.__ui.button12, self.__ui.button13, self.__ui.button14, self.__ui.button15,
            self.__ui.button16, self.__ui.button17, self.__ui.button18, self.__ui.button19,
            self.__ui.button20, self.__ui.button21, self.__ui.button22, self.__ui.button23,
        ]
        self.__operation_to_perform = None
        self.__src_pos = None
        self.__setup_buttons()

    def startGUI(self):
        self.__ui.label.setText("Enter position to place piece")
        self.__operation_to_perform = GUI.GET_POS_TO_PLACE
        self.__mainwindow.show()
        self.__app.exec()

    def __setup_buttons(self):
        send_param = lambda val: lambda: self.__button_clicked(val)
        for i in range(24):
            self.__buttons[i].clicked.connect(send_param(i))
            self.__buttons[i].setCursor(QCursor(Qt.PointingHandCursor))

    def __button_clicked(self, val: int):
        try:
            self.perform_operation(val)
        except Exception as e:
            self.show_pop_up("Error", e.__str__(), QMessageBox.Critical)
            self.go_back_to_beginning_of_operation()

    def perform_operation(self, val: int):
        if self.__operation_to_perform == GUI.GET_POS_TO_PLACE:
            self.__serv.place(val)
            self.update_gui_board()
            self.check_and_handle_morris_created(val)

        elif self.__operation_to_perform == GUI.GET_POS_TO_MOVE:
            self.__src_pos = val
            self.__operation_to_perform = GUI.GET_POS_TO_MOVE_TO
            self.update_gui_board()
            self.__ui.label.setText("Enter position where to move")

        elif self.__operation_to_perform == GUI.GET_POS_TO_MOVE_TO:
            self.__serv.move(self.__src_pos, val)
            self.update_gui_board()
            self.__src_pos = None
            self.check_and_handle_morris_created(val)

        elif self.__operation_to_perform == GUI.GET_POS_TO_JUMP:
            self.__src_pos = val
            self.__operation_to_perform = GUI.GET_POS_TO_JUMP_TO
            self.update_gui_board()
            self.__ui.label.setText("Enter position where to jump")

        elif self.__operation_to_perform == GUI.GET_POS_TO_JUMP_TO:
            self.__serv.jump(self.__src_pos, val)
            self.update_gui_board()
            self.__src_pos = None
            self.check_and_handle_morris_created(val)

        elif self.__operation_to_perform == GUI.GET_POS_TO_REMOVE:
            was_removed = self.__serv.remove(val)
            if not was_removed:
                raise ValueError("removal invalid")
            self.update_gui_board()
            self.prepare_next_operation()

    def go_back_to_beginning_of_operation(self):
        if self.__operation_to_perform == GUI.GET_POS_TO_MOVE_TO:
            self.__operation_to_perform = GUI.GET_POS_TO_MOVE
            self.update_gui_board()
            self.__ui.label.setText("Enter position of piece to move")
        elif self.__operation_to_perform == GUI.GET_POS_TO_JUMP_TO:
            self.__operation_to_perform = GUI.GET_POS_TO_JUMP
            self.update_gui_board()
            self.__ui.label.setText("Enter position of piece to be jumped")

    def prepare_next_operation(self):
        try:
            self.__serv.switch_player()
            self.handle_computer_turn()
            self.__serv.switch_player()
        except GameOver as go:
            self.show_pop_up("Game over", go.__str__(), QMessageBox.Information)
            self.__app.quit()

        phase = self.__serv.get_phase_of_active_player()
        if phase == Gameplay.PLACEMENT_PHASE:
            self.__operation_to_perform = GUI.GET_POS_TO_PLACE
            self.__ui.label.setText("Enter position to place piece")
        elif phase == Gameplay.MOVING_PHASE:
            self.__operation_to_perform = GUI.GET_POS_TO_MOVE
            self.__ui.label.setText("Enter position of piece to move")
        elif phase == Gameplay.JUMPING_PHASE:
            self.__operation_to_perform = GUI.GET_POS_TO_JUMP
            self.__ui.label.setText("Enter position of piece to be jumped")

    def handle_computer_turn(self):
        self.__serv.handle_computer_turn()
        self.update_gui_board_delayed()

    def check_and_handle_morris_created(self, pos: int):
        if self.__serv.is_pos_in_morris(pos):
            self.__ui.label.setText("New morris created. Choose piece to remove")
            self.__operation_to_perform = GUI.GET_POS_TO_REMOVE
            self.update_gui_board()
        else:
            self.prepare_next_operation()

    def update_gui_board(self):
        """
        UPDATE BUTTON APPEARANCE
        """
        board = self.__serv.get_board()
        check = self.__operation_to_perform in [
            GUI.GET_POS_TO_PLACE,
            GUI.GET_POS_TO_MOVE_TO,
            GUI.GET_POS_TO_JUMP_TO
        ]
        for i in range(24):
            if board[i] == 1:
                self.__buttons[i].setStyleSheet(GUI.HUMAN_PLAYER_STYLESHEET)
                self.__buttons[i].setDisabled(check)
            elif board[i] == 2:
                self.__buttons[i].setStyleSheet(GUI.COMPUTER_PLAYER_STYLESHEET)
                self.__buttons[i].setDisabled(check)
            else:
                self.__buttons[i].setStyleSheet(GUI.EMPTY_POS_STYLESHEET)
                self.__buttons[i].setDisabled(not check)

    def update_gui_board_delayed(self):
        timer = QTimer(self.__mainwindow)
        timer.timeout.connect(lambda: self.update_gui_board())
        timer.setInterval(1000)
        timer.setSingleShot(True)
        timer.start()

    @staticmethod
    def show_pop_up(title: str, message: str, icon):
        mess_box = QMessageBox(None, None, None)
        mess_box.setText(message)
        mess_box.setWindowTitle(title)
        mess_box.setIcon(icon)
        mess_box.exec()
