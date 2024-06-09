from src.repository.bin_file_repository import BinaryFileRepository
from ui.ui import UI
from repository.memory_repository import MemoryRepository
from repository.client_txt_repository import ClientTextFileRepository
from repository.movie_txt_repository import MovieTextFileRepository
from repository.rental_txt_repository import RentalTextFileRepository
from services.rental_services import RentalServices
from services.client_services import ClientServices
from services.movie_services import MovieServices
from services.undo_redo_service import UndoService
from domain.rental import generate_rentals
from jproperties import Properties
from pathlib import Path


def read_settings():
    path = Path(__file__).parent / "settings.properties"
    configs = Properties()
    with path.open('rb') as config_file:
        configs.load(config_file)
    return {
        "repo_type": configs.get("repository")[0],
        "movies_file": configs.get("movies")[0],
        "clients_file": configs.get("clients")[0],
        "rentals_file": configs.get("rentals")[0]
    }


data = read_settings()

movie_repo = None
client_repo = None
rental_repo = None

if data["repo_type"] == "inmemory":
    movie_repo = MemoryRepository()
    client_repo = MemoryRepository()
    rental_repo = MemoryRepository()

    movies, clients, rentals = generate_rentals(20)
    for m in movies:
        movie_repo.add(m)
    for c in clients:
        client_repo.add(c)
    for r in rentals:
        rental_repo.add(r)

elif data["repo_type"] == "binaryfiles":
    movie_repo = BinaryFileRepository("../data/"+data["movies_file"])
    client_repo = BinaryFileRepository("../data/"+data["clients_file"])
    rental_repo = BinaryFileRepository("../data/"+data["rentals_file"])

elif data["repo_type"] == "textfiles":
    movie_repo = MovieTextFileRepository("../data/"+data["movies_file"])
    client_repo = ClientTextFileRepository("../data/"+data["clients_file"])
    rental_repo = RentalTextFileRepository("../data/"+data["rentals_file"])

    # movies, clients, rentals = generate_rentals(20)
    # for m in movies:
    #     movie_repo.add(m)
    # for c in clients:
    #     client_repo.add(c)
    # for r in rentals:
    #     rental_repo.add(r)

undo_serv = UndoService()
rental_serv = RentalServices(rental_repo, movie_repo, client_repo, undo_serv)
movie_serv = MovieServices(movie_repo, undo_serv, rental_serv)
client_serv = ClientServices(client_repo, undo_serv, rental_serv)


app = UI(rental_serv, movie_serv, client_serv, undo_serv)


if __name__ == "__main__":
    app.start()
    