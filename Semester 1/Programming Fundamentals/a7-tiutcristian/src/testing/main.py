from src.domain import Book
from src.repository import Repository
import unittest


class TestBook(unittest.TestCase):
    def setUp(self):
        print("\nRunning setUp method...")
        self.book1 = Book("ISBN TEST 1", "Author test 1", "Title test 1")
        self.book2 = Book("ISBN TEST 2", "Author test 2", "Title test 2")
        self.book3 = Book("ISBN TEST 3", "Author test 3", "Title test 3")

        self.repo1 = Repository()
        self.repo1.add_book(self.book1)

        self.repo2 = Repository()
        self.repo2.add_book(self.book2)
        self.repo2.add_book(self.book3)

    def tearDown(self):
        print("Running tearDown method...")

    def test_add_book(self):
        print("Running test_reading_time...")
        self.assertEqual(self.repo1.get_curr_list(), [self.book1])
        self.assertEqual(self.repo2.get_curr_list(), [self.book2, self.book3])


if __name__ == "__main__":
    unittest.main()
