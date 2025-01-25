DROP TABLE IF EXISTS Users;

CREATE TABLE Users(
    id INT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    password VARCHAR(255)
);

-- 1 to n relation
CREATE TABLE Posts(
    id INT PRIMARY KEY,
    title VARCHAR(100),
    content TEXT,
    user_id INT,
    FOREIGN KEY(user_id) REFERENCES Users(id)
);

-- create a column to an existing table
ALTER TABLE Users ADD COLUMN cnp VARCHAR(13);

-- drop a column
ALTER TABLE Users DROP COLUMN cnp;

-- for n to n relation
CREATE TABLE Student_Courses(
    student_id INT,
    course_id INT,
    enrollment_date DATE,
    PRIMARY KEY(student_id, course_id),
    FOREIGN KEY(student_id) REFERENCES Users(id),
    FOREIGN KEY(course_id) REFERENCES Courses(id)
);

-- 1 to 1 relation - unique constraint
CREATE TABLE Profiles(
    id INT PRIMARY KEY,
    user_id INT UNIQUE,
    bio TEXT,
    FOREIGN KEY(user_id) REFERENCES Users(id)
);