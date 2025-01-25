-- Triathlon

    -- 1. Coaches
        -- id
        -- name
        -- email
        -- experience

    -- 2. Teams
        -- id
        -- name
        -- country
        -- coach_id (unique)

    -- 3. Athletes
        -- id
        -- name
        -- email
        -- team_id

    -- 4. SwimPools
        -- id
        -- name
        -- location
        -- length
        -- width
        -- depth

    -- 5. BikeTracks
        -- id
        -- name
        -- location
        -- length
        -- difficulty

    -- 6. RunTracks
        -- id
        -- name
        -- location
        -- length
        -- difficulty

    -- 7. Events
        -- id
        -- name
        -- location

    -- 8. Races
        -- id
        -- name
        -- date
        -- swim_pool_id
        -- bike_track_id
        -- run_track_id
        -- event_id

    -- 9. RaceResults
        -- id
        -- athlete_id
        -- race_id
        -- place_occupied
        -- total_time
        -- swim_time
        -- bike_time
        -- run_time

    -- 10. Sponsors
        -- id
        -- name
        -- country

    -- 11. Sponsorships [n to n]
        -- sponsor_id
        -- athlete_id
        -- amount
        -- start_date
        -- end_date


-- remove all connections to the database
USE [master];
DECLARE @kill varchar(8000) = '';  
SELECT @kill = @kill + 'kill ' + CONVERT(varchar(5), session_id) + ';'  
FROM sys.dm_exec_sessions
WHERE database_id  = db_id('Triathlon')
EXEC(@kill);
-- drop the database
DROP DATABASE IF EXISTS Triathlon;
-- create the database
CREATE DATABASE Triathlon;
-- use the database
USE Triathlon;

CREATE TABLE Coaches(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    email VARCHAR(100),
    experience INT
);

CREATE TABLE Teams(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    country VARCHAR(100),
    coach_id INT,
    FOREIGN KEY(coach_id) REFERENCES Coaches(id) ON DELETE SET NULL
);

CREATE UNIQUE NONCLUSTERED INDEX coach_id
ON Teams(coach_id)
WHERE coach_id IS NOT NULL;

CREATE TABLE Athletes(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    email VARCHAR(100),
    team_id INT,
    FOREIGN KEY(team_id) REFERENCES Teams(id) ON DELETE SET NULL
);

CREATE TABLE SwimPools(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    location VARCHAR(100),
    length INT,
    width INT,
    depth INT
);

CREATE TABLE BikeTracks(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    location VARCHAR(100),
    length INT,
    difficulty INT
);

CREATE TABLE RunTracks(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    location VARCHAR(100),
    length INT,
    difficulty INT
);

CREATE TABLE Events(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    location VARCHAR(100)
);

CREATE TABLE Races(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    date DATE,
    swim_pool_id INT,
    bike_track_id INT,
    run_track_id INT,
    event_id INT,
    FOREIGN KEY(swim_pool_id) REFERENCES SwimPools(id) ON DELETE SET NULL,
    FOREIGN KEY(bike_track_id) REFERENCES BikeTracks(id) ON DELETE SET NULL,
    FOREIGN KEY(run_track_id) REFERENCES RunTracks(id) ON DELETE SET NULL,
    FOREIGN KEY(event_id) REFERENCES Events(id) ON DELETE SET NULL
);

CREATE TABLE RaceResults(
    id INT PRIMARY KEY IDENTITY(1,1),
    athlete_id INT,
    race_id INT,
    place_occupied INT,
    total_time INT,
    swim_time INT,
    bike_time INT,
    run_time INT,
    FOREIGN KEY(athlete_id) REFERENCES Athletes(id) ON DELETE CASCADE,
    FOREIGN KEY(race_id) REFERENCES Races(id) ON DELETE CASCADE
);

CREATE TABLE Sponsors(
    id INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(100),
    country VARCHAR(100)
);

CREATE TABLE Sponsorships(
    sponsor_id INT,
    athlete_id INT,
    amount INT,
    start_date DATE,
    end_date DATE,
    PRIMARY KEY(sponsor_id, athlete_id),
    FOREIGN KEY(sponsor_id) REFERENCES Sponsors(id) ON DELETE CASCADE,
    FOREIGN KEY(athlete_id) REFERENCES Athletes(id) ON DELETE CASCADE
);