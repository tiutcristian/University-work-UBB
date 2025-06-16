CREATE DATABASE TrainManagement;

USE TrainManagement;

CREATE TABLE TrainTypes (
    TypeID INT PRIMARY KEY,
    TypeName VARCHAR(50),
    TypeDescription VARCHAR(100)
);

CREATE TABLE Trains (
    TrainID INT PRIMARY KEY,
    TrainName VARCHAR(50),
    TypeID INT,
    FOREIGN KEY (TypeID) REFERENCES TrainTypes(TypeID)
);

CREATE TABLE Stations (
    StationID INT PRIMARY KEY,
    StationName VARCHAR(50) UNIQUE
);

CREATE TABLE Routes (
    RouteID INT PRIMARY KEY,
    RouteName VARCHAR(50) UNIQUE,
    TrainID INT REFERENCES Trains(TrainID)
);

CREATE TABLE StationRoutes (
    RouteID INT REFERENCES Routes(RouteID),
    StationID INT REFERENCES Stations(StationID),
    ArrivalTime TIME,
    DepartureTime TIME,
    PRIMARY KEY (RouteID, StationID)
);



CREATE PROCEDURE AddStationToRoute
    @RouteID INT,
    @StationID INT,
    @ArrivalTime TIME,
    @DepartureTime TIME
AS
BEGIN
    IF NOT EXISTS (SELECT * FROM Routes WHERE RouteID = @RouteID) BEGIN
        RAISERROR('Route does not exist', 16, 1);
        RETURN;
    END

    IF NOT EXISTS (SELECT * FROM Stations WHERE StationID = @StationID) BEGIN
        RAISERROR('Station does not exist', 16, 1);
        RETURN;
    END

    IF EXISTS (
        SELECT * 
        FROM StationRoutes 
        WHERE RouteID = @RouteID AND StationID = @StationID
    ) BEGIN
        UPDATE StationRoutes
        SET ArrivalTime = @ArrivalTime, DepartureTime = @DepartureTime
        WHERE RouteID = @RouteID AND StationID = @StationID;
    END ELSE BEGIN
        INSERT INTO StationRoutes VALUES (@RouteID, @StationID, @ArrivalTime, @DepartureTime);
    END
END;



CREATE VIEW RoutesThroughAllStations AS
    SELECT RouteName
    FROM Routes r
    WHERE NOT EXISTS (
        SELECT StationID
        FROM Stations s
        WHERE NOT EXISTS (
            SELECT DISTINCT StationID
            FROM StationRoutes
            WHERE RouteID = r.RouteID AND StationID = s.StationID
        )
    );



CREATE FUNCTION StationsWithMoreThanR(@R INT)
RETURNS TABLE
AS
RETURN (
    SELECT StationName
    FROM Stations s
    WHERE @R < (
        SELECT COUNT(*)
        FROM StationRoutes
        WHERE StationID = s.StationID
    )
);