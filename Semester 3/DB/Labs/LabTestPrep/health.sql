-- Create a database for a health tracking system. The entities of interest to the problem domain are:
-- Users, Activities, Meals, Health Metries and User Activities Journal. A user has a name, an age
-- and a gender. Names are unique. An activity has a name and a number of calories burned per
-- hour. Names are unique. A meal has a name and a number of calories per serving. Names are
-- unique. The system stores data about health metrics: user, date of recording, weight, blood
-- pressure and heart rate. Users can perform multiple activities. The system will store the date when
-- the activity was performed and the duration (in minutes).


-- Users
    -- id                   INT (PK)
    -- name (unique)        VARCHAR
    -- age                  INT
    -- gender               CHAR (M/F)

-- Activities
    -- activityId           INT (PK)
    -- name (unique)        VARCHAR
    -- caloriesPerHour      INT

-- Meals
    -- mealId               INT (PK)
    -- name (unique)        VARCHAR
    -- caloriesPerServing   INT

-- HealthMetrics
    -- metricId             INT (PK)
    -- userId               INT
    -- dateOfRecording      DATE
    -- weight               DECIMAL
    -- blood pressure       VARCHAR
    -- heartRate            INT

-- UserActivitiesJournal
    -- userId               INT
    -- activityId           INT
    -- dateOfRecording      DATE
    -- durationInMinutes    INT
    -- PK: (userId, activityId, dateOfRecording)


-- 1. Write an SQL script that creates the corresponding relational data model.
CREATE DATABASE [Health];

USE [Health];

CREATE TABLE Users (
    id INT PRIMARY KEY,
    name VARCHAR(255) UNIQUE,
    age INT,
    gender CHAR(1)
);

CREATE TABLE Activities (
    activityId INT PRIMARY KEY,
    name VARCHAR(255) UNIQUE,
    caloriesPerHour INT
);

CREATE TABLE Meals (
    mealId INT PRIMARY KEY,
    name VARCHAR(255) UNIQUE,
    caloriesPerServing INT
);

CREATE TABLE HealthMetrics (
    metricId INT PRIMARY KEY,
    userId INT,
    dateOfRecording DATE,
    weight DECIMAL,
    bloodPressure VARCHAR(255),
    heartRate INT
);

CREATE TABLE UserActivitiesJournal (
    userId INT,
    activityId INT,
    dateOfRecording DATE,
    durationInMinutes INT,
    PRIMARY KEY (userId, activityId, dateOfRecording)
);


-- 2. Implement a stored procedure that receives the details of a health metric and adds the metric
-- in the database. If the date of recording is in the future (e.g. today is 05-01-2024 and the date of
-- recording for the health metric is 06-01-2024), the system will display an error message and it
-- will not save the health metric in the database.
GO
CREATE PROCEDURE AddHealthMetric(
    @userId INT,
    @dateOfRecording DATE,
    @weight DECIMAL,
    @bloodPressure VARCHAR(255),
    @heartRate INT
) AS
BEGIN
    IF @dateOfRecording > GETDATE() BEGIN
        RAISERROR('The date of recording cannot be in the future.', 16, 1);
    END ELSE BEGIN
        INSERT INTO HealthMetrics (userId, dateOfRecording, weight, bloodPressure, heartRate)
        VALUES (@userId, @dateOfRecording, @weight, @bloodPressure, @heartRate);
    END
END
GO


-- 3. Create a view that displays the average weight and the maximum blood pressure for each user
-- based on the data recorded during the last year (2023).
GO
CREATE VIEW UserHealthSummary AS
    SELECT u.name AS userName, AVG(hm.weight) AS avgWeight, MAX(hm.bloodPressure) AS maxBloodPressure
    FROM Users u
    JOIN HealthMetrics hm ON u.id = hm.userId
    WHERE hm.dateOfRecording BETWEEN '2023-01-01' AND '2023-12-31'
    GROUP BY u.name;
GO


-- 4. Implement a function that returns the average duration of a specific activity A for a given user
-- U , where A and U are function parameters.
GO
CREATE FUNCTION GetAverageDurationForActivity(
    @U VARCHAR(255),
    @A VARCHAR(255)
) 
RETURNS INT AS 
BEGIN
    DECLARE @avgDuration INT;
    SELECT @avgDuration = AVG(durationInMinutes)
    FROM UserActivitiesJournal uaj
    JOIN Users u ON uaj.userId = u.id
    JOIN Activities a ON uaj.activityId = a.activityId
    WHERE u.name = @U AND a.name = @A;
    RETURN @avgDuration;
END
GO