[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/MrnA3ZI7)
# 💻 Assignment 07
## Requirements

- Use classes to represent the following:
    - The `UI` class
    - A `Services` class that implements the required functionalities
    - The domain entity (`complex`,  `expense`,  `student`, `book`) class
    - A `Repository` class whose job it is to store the domain entity instances. This class will have three implementations: 
      - (1) a `MemoryRepository`, which stores domain instances in memory (just like in previous assignments); 
      - (2) a `TextFileRepository`, which persists domain entities to a text file
      - (3) a `BinaryFileRepository`, which persists domain entities using object serialization with [Pickle](https://docs.python.org/3.10/library/pickle.html). 
      
      You should be able to switch between which repository is in use by changing the instantiated class. When using a file-backed repository, changes made while running the program must be persisted across runs.  
- Have 10 programmatically generated entries in the application at start-up. Save these to the text/binary input files.
- Unit tests and specifications for non-UI functions related to the first functionality.

## Problem Statement
### 4. Books
Each book has: 
- an `isbn` (string, unique)
- an `author`
- a `title` (strings). 

Provide the following features:
1. Add a book. (book data is read from the console)
2. Display the list of books.
3. Filter the list so that book titles starting with a given word are deleted from the list.
4. Undo the last operation that modified program data. This step can be repeated. The user can undo only those operations made during the current run of the program.

## Bonus possibility (0.1p, deadline week 10)
- In addition to the file-based implementations above, implement a repository that uses either a JSON or an XML file for storage (at your choice).

## Bonus possibility (0.1p, deadline week 10)
- Use a `settings.properties` file to decide which of the repository implementations to use. At startup, the program reads this input file and instantiates the correct repository. This allows changing the program's input file format without changing its source code.

## Bonus possibility (0.1p, deadline week 10)
- Implement a database-backed (SQL or NoSQL) repository. Use the database system’s update functionalities properly (don’t rewrite the entire database at each operation).
