from ui import UI
from services import Services


if __name__ == "__main__":
    repo_type = Services.get_repo_type()
    serv = Services(repo_type)
    ui = UI(serv)
    ui.start()
