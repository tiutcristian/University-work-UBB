from ui.ui import UI
from repository.repository import Repository
from services.rental_services import RentalServices
from services.client_services import ClientServices
from services.movie_services import MovieServices
from domain.rental import generate_rentals

movie_repo = Repository()
client_repo = Repository()
rental_repo = Repository()

movies, clients, rentals = generate_rentals(20)

for m in movies:
    movie_repo.add(m)

for c in clients:
    client_repo.add(c)

for r in rentals:
    rental_repo.add(r)

rental_serv = RentalServices(rental_repo, movie_repo, client_repo)
movie_serv = MovieServices(movie_repo)
client_serv = ClientServices(client_repo)

app = UI(rental_serv, movie_serv, client_serv)


if __name__ == "__main__":
    app.start()
    