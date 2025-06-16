CREATE TABLE Authors (
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100) NOT NULL UNIQUE
);

CREATE TABLE Books (
    id INT PRIMARY KEY IDENTITY(1,1),
    authorId INT NOT NULL,
    title VARCHAR(50) NOT NULL,
    genre VARCHAR(20) NOT NULL,
    publicationYear INT CHECK (publicationYear >= 2000),
    FOREIGN KEY (authorId) REFERENCES Authors(id) ON DELETE CASCADE
);

CREATE TABLE Members (
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(20) NOT NULL,
    startDate DATE NOT NULL CHECK (startDate <= GETDATE()),
    maximumAmountToRent INT Default 5
);

CREATE TABLE Rentals (
    bookId INT NOT NULL,
    memberId INT NOT NULL,
    rentalDate DATE NOT NULL,
    returnDate DATE,
    PRIMARY KEY (bookId, memberId),
    FOREIGN KEY (bookId) REFERENCES Books(id),
    FOREIGN KEY (memberId) REFERENCES Members(id),
    CHECK (returnDate >= rentalDate AND DATEDIFF(DAY, rentalDate, returnDate) <= 30)
);