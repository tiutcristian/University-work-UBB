USE [master];
DECLARE @kill varchar(8000) = '';  
SELECT @kill = @kill + 'kill ' + CONVERT(varchar(5), session_id) + ';'  
FROM sys.dm_exec_sessions
WHERE database_id  = db_id('PracticDBMS')
EXEC(@kill);
DROP DATABASE IF EXISTS PracticDBMS;
CREATE DATABASE PracticDBMS;
USE PracticDBMS;

CREATE TABLE SemesterProject (
    id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL
);

CREATE TABLE ProjectTeam (
    id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL,
    number INT NOT NULL,
    semester_project_id INT NOT NULL,
    FOREIGN KEY (semester_project_id) REFERENCES SemesterProject(id)
);

CREATE TABLE StudentMember (
    id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL,
    role NVARCHAR(50) NOT NULL,
    project_team_id INT NOT NULL,
    FOREIGN KEY (project_team_id) REFERENCES ProjectTeam(id)
);

CREATE TABLE Task (
    id INT IDENTITY(1,1) PRIMARY KEY,
    description NVARCHAR(255) NOT NULL,
    student_member_id INT NOT NULL,
    FOREIGN KEY (student_member_id) REFERENCES StudentMember(id)
);

CREATE TABLE SoftwareTool (
    id INT IDENTITY(1,1) PRIMARY KEY,
    name NVARCHAR(100) NOT NULL,
    description NVARCHAR(255) NOT NULL
);

CREATE TABLE License (
    id INT IDENTITY(1,1) PRIMARY KEY,
    project_team_id INT NOT NULL,
    software_tool_id INT NOT NULL,
    available_days_no INT NOT NULL,
    FOREIGN KEY (project_team_id) REFERENCES ProjectTeam(id),
    FOREIGN KEY (software_tool_id) REFERENCES SoftwareTool(id)
);

INSERT INTO SemesterProject (name) VALUES ('Project 1');

INSERT INTO ProjectTeam (name, number, semester_project_id)
VALUES ('Team 1', 1, 1),
       ('Team 2', 2, 1),
       ('Team 3', 3, 1);

INSERT INTO StudentMember (name, role, project_team_id)
VALUES ('Nume1', 'Developer', 1),
       ('Nume2', 'Tester', 1),
       ('Nume3', 'Developer', 2),
       ('Nume4', 'Tester', 2),
       ('Nume5', 'Developer', 3),
       ('Nume6', 'Tester', 3);