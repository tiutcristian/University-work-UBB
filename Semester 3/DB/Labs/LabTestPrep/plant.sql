-- Create a database for a plant management system. The entities of interest to the problem domain are: 
    -- Plants
        -- plantId          INT     (PK)
        -- name             VARCHAR (unique)
        -- description      TEXT
        -- acquisitionDate  DATE
        -- lastWateredDate  DATE
        -- locationID       INT     (FK)

    -- Categories
        -- categoryId       INT     (PK)
        -- name             VARCHAR (unique)
        -- description      TEXT

    -- PlantCategories
        -- plantID          INT     (FK)
        -- categoryID       INT     (FK)

    -- Locations
        -- locationId       INT     (PK)
        -- name             VARCHAR (unique)
        -- description      TEXT

    -- Images 
        -- imageId          INT     (PK)
        -- path             VARCHAR
        -- caption          TEXT
        -- uploadDate       DATE
        -- plantId          INT     (FK)

    -- CareHistory
        -- careHistoryId        INT     (PK)
        -- wateringDateTime     DATETIME
        -- notes                TEXT
        -- plantId              INT     (FK)
    
-- [DONE] Each location can be associated with multiple plants.  
-- [DONE] Each plant can have multiple images uploaded and can belong to multiple categories.
-- [DONE] Each category can encompass multiple plants.



-- 1. Write an SQL script that creates the corresponding relational data model.
CREATE DATABASE Plants;

USE [Plants];

CREATE TABLE Locations (
    locationId INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(255) UNIQUE,
    description TEXT
);

CREATE TABLE Plants (
    plantId INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(255) UNIQUE,
    description TEXT,
    acquisitionDate DATE,
    lastWateredDate DATE,
    locationID INT,
    FOREIGN KEY (locationID) REFERENCES Locations(locationId)
);

CREATE TABLE Categories (
    categoryId INT PRIMARY KEY IDENTITY(1,1),
    name VARCHAR(255) UNIQUE,
    description TEXT
);

CREATE TABLE PlantCategories (
    plantID INT,
    categoryID INT,
    FOREIGN KEY (plantID) REFERENCES Plants(plantId),
    FOREIGN KEY (categoryID) REFERENCES Categories(categoryId)
);

CREATE TABLE Images (
    imageId INT PRIMARY KEY IDENTITY(1,1),
    path VARCHAR(255),
    caption TEXT,
    uploadDate DATE,
    plantId INT,
    FOREIGN KEY (plantId) REFERENCES Plants(plantId)
);

CREATE TABLE CareHistory (
    careHistoryId INT PRIMARY KEY IDENTITY(1,1),
    wateringDateTime DATETIME,
    notes TEXT,
    plantId INT,
    FOREIGN KEY (plantId) REFERENCES Plants(plantId)
);


-- 2. Implement a stored procedure that receives the details of a plant and adds the plant in the DATABASE.
-- IF EXISTS plant with same name UPDATE ACQUISITION DATE
GO
CREATE PROCEDURE AddOrUpdatePlant(
    @name VARCHAR,
    @description TEXT,
    @acquisitionDate DATE,
    @lastWateredDate DATE,
    @locationID INT
) AS 
BEGIN
    IF NOT EXISTS (SELECT * FROM Locations WHERE locationId = @locationID) BEGIN
        RAISERROR('Location does not exist', 16, 1);
        RETURN;
    END

    IF EXISTS (SELECT * FROM Plants WHERE name = @name) BEGIN
        UPDATE Plants
        SET acquisitionDate = @acquisitionDate
        WHERE name = @name
    END ELSE BEGIN
        INSERT INTO Plants VALUES (@name, @description, @acquisitionDate, @lastWateredDate, @locationID)
    END
END
GO



-- 3. Create a view that displays the total number of plants and the latest acquisition date for each location.
GO
CREATE VIEW LocationDataByPlants AS
    SELECT locationID, COUNT(*) AS noOfPlants, MAX(acquisitionDate) AS latestAcquisitionDate
    FROM Plants
    GROUP BY locationID
GO



-- 4. Implement a function that returns the plant with minimum X uploaded images and that has
-- been cared for most recently, where X is a function parameter.
GO
CREATE OR ALTER FUNCTION PlantWithMinXImgAndCaredMostRecently(@X INT)
RETURNS TABLE
AS
RETURN (
    SELECT TOP 1 p.plantId, COUNT(i.imageId) AS noOfImages, MAX(ch.wateringDateTime) AS lastWateredDate
    FROM Plants p
    JOIN Images i ON p.plantId = i.plantId
    JOIN CareHistory ch ON p.plantId = ch.plantId
    GROUP BY p.plantId
    HAVING COUNT(i.imageId) >= @X
    ORDER BY MAX(ch.wateringDateTime) DESC
)
GO