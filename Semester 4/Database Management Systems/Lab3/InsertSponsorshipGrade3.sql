USE [Triathlon]

DELETE FROM Sponsorships
DELETE FROM Athletes
DELETE FROM Sponsors
GO

CREATE OR ALTER PROCEDURE InsertSponsorshipGrade3
    @AthleteName NVARCHAR(100),
    @SponsorName NVARCHAR(100),
    @StartDate DATE,
    @EndDate DATE
AS
BEGIN
    SET NOCOUNT ON;
    DECLARE @AthleteID INT, @SponsorID INT;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- Validate parameters
        IF @AthleteName IS NULL OR @SponsorName IS NULL OR @StartDate IS NULL
            THROW 50000, 'AthleteName, SponsorName, and StartDate cannot be null.', 1;

        -- Insert Athlete
        INSERT INTO Athletes ([name]) VALUES (@AthleteName);
        SET @AthleteID = SCOPE_IDENTITY();

        -- Insert Sponsor
        INSERT INTO Sponsors ([name]) VALUES (@SponsorName);
        SET @SponsorID = SCOPE_IDENTITY();

        -- Insert Sponsorship
        INSERT INTO Sponsorships (athlete_id, sponsor_id, [start_date], end_date)
        VALUES (@AthleteID, @SponsorID, @StartDate, @EndDate);

        COMMIT TRANSACTION;
        INSERT INTO Logs (Action) VALUES ('InsertSponsorshipGrade3 succeeded.');
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        INSERT INTO Logs (Action, ErrorMessage)
        VALUES ('InsertSponsorshipGrade3 failed', ERROR_MESSAGE());
        THROW;
    END CATCH
END;
GO



-- Test cases

-- Arrange
SELECT * FROM Athletes;
SELECT * FROM Sponsors;
SELECT * FROM Sponsorships;
SELECT * FROM Logs;
DELETE FROM Logs;
DELETE FROM Sponsorships
DELETE FROM Athletes
DELETE FROM Sponsors

-- 1. Happy scenario
EXEC InsertSponsorshipGrade3 
    @AthleteName = 'Cristiano Ronaldo', 
    @SponsorName = 'Nike', 
    @StartDate = '2023-01-01', 
    @EndDate = '2024-01-01';

-- 2. Error scenario: 
--      repeat the same name for the sponsor 
--      (Sponsors table has a unique constraint on name)
EXEC InsertSponsorshipGrade3 
    @AthleteName = 'Lionel Messi', 
    @SponsorName = 'Nike', 
    @StartDate = '2023-01-01', 
    @EndDate = '2024-01-01';