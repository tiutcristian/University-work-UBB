from src.domain.client import Client
from src.domain.movie import Movie
from src.repository.repository import Repository
import unittest


# First functionality:
# Manage clients and movies (i.e. IdObject). (add, remove, update)

class TestBook(unittest.TestCase):
    def setUp(self):
        print("\nRunning setUp method...")

        self.repo1 = Repository()
        self.repo2 = Repository()

        self.client1 = Client(201, "Charlie Williams")
        self.client2 = Client(202, "Frank Johnson")
        self.client3 = Client(203, "John Brown")

        self.movie1 = Movie(201, "Title movie 1", "Description movie 1", "Genre movie 1")
        self.movie2 = Movie(202, "Title movie 2", "Description movie 2", "Genre movie 2")
        self.movie3 = Movie(203, "Title movie 3", "Description movie 3", "Genre movie 3")

    def tearDown(self):
        print("Running tearDown method...")

    def test_add(self):
        print("Testing add...")

        self.repo1.add(self.client1)
        self.repo1.add(self.movie2)
        self.repo1.add(self.client3)
        self.assertEqual(
            self.repo1.get_data(),
            {
                201: self.client1,
                202: self.movie2,
                203: self.client3
            }
        )

        # -------------------------

        self.repo2.add(self.movie1)
        self.repo2.add(self.client3)
        self.repo2.add(self.client2)
        self.assertEqual(
            self.repo2.get_data(),
            {
                201: self.movie1,
                202: self.client2,
                203: self.client3
            }
        )

    def test_update_client(self):
        print("Testing update...")

        self.repo1.add(self.client1)
        self.repo1.add(self.movie2)
        self.repo1.add(self.client3)

        self.repo1.update(202, self.client1)
        self.repo1.update(201, self.movie3)

        self.assertEqual(
            self.repo1.get_data(),
            {
                201: self.movie3,
                202: self.client1,
                203: self.client3
            }
        )

        # -------------------------

        self.repo2.add(self.movie1)
        self.repo2.add(self.client3)
        self.repo2.add(self.client2)

        self.repo2.update(201, self.client2)
        self.repo2.update(203, self.movie2)

        self.assertEqual(
            self.repo2.get_data(),
            {
                201: self.client2,
                202: self.client2,
                203: self.movie2
            }
        )

    def test_delete_client(self):
        print("Testing delete...")

        self.repo1.add(self.client1)
        self.repo1.add(self.movie2)
        self.repo1.add(self.client3)

        self.repo1.remove(202)

        self.assertEqual(
            self.repo1.get_data(),
            {
                201: self.client1,
                203: self.client3
            }
        )

        # -------------------------

        self.repo2.add(self.movie1)
        self.repo2.add(self.client3)
        self.repo2.add(self.client2)

        self.repo2.remove(203)
        self.repo2.remove(201)

        self.assertEqual(
            self.repo2.get_data(),
            {
                202: self.client2
            }
        )


if __name__ == "__main__":
    unittest.main()
