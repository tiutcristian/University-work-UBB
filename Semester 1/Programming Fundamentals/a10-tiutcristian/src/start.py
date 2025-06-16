from src.domain.board import Board
from src.services.services import Gameplay
from src.ui.gui_main import GUI
from ui.console_ui import ConsoleUI


def run_gui(services: Gameplay):
    gui = GUI(services)
    gui.startGUI()


def run_cui(services: Gameplay):
    ui = ConsoleUI(services)
    ui.start_ui()


if __name__ == '__main__':
    """create repo"""
    board = Board()

    """create gameplay"""
    serv = Gameplay(board)

    """run UI (console/graphical)"""
    # run_cui(serv)
    run_gui(serv)
