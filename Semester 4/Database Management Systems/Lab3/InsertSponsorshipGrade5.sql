USE [Triathlon]

CREATE OR ALTER PROCEDURE InsertSponsorshipGrade5
    @AthleteName NVARCHAR(100),
    @SponsorName NVARCHAR(100),
    @StartDate DATE,
    @EndDate DATE
AS
BEGIN
    SET NOCOUNT ON;
    DECLARE @AthleteID INT, @SponsorID INT;
    DECLARE @rollBackPointAthletes INT,
            @rollBackPointSponsors INT,
            @rollBackPointSponsorships INT;

    BEGIN TRANSACTION
        BEGIN TRY

        -- Validate parameters
        IF @AthleteName IS NULL OR @SponsorName IS NULL OR @StartDate IS NULL
            THROW 50000, 'AthleteName, SponsorName, and StartDate cannot be null.', 1;

        -- Insert Athlete
        INSERT INTO Athletes ([name]) VALUES (@AthleteName);
        SET @AthleteID = SCOPE_IDENTITY();
        SAVE TRANSACTION InsertIntoAthletes;
        SET @rollBackPointAthletes = 1;

        -- Insert Sponsor
        INSERT INTO Sponsors ([name]) VALUES (@SponsorName);
        SET @SponsorID = SCOPE_IDENTITY();
        SAVE TRANSACTION InsertIntoSponsors;
        SET @rollBackPointSponsors = 1;

        -- Insert Sponsorship
        INSERT INTO Sponsorships (athlete_id, sponsor_id, [start_date], end_date)
        VALUES (@AthleteID, @SponsorID, @StartDate, @EndDate);
        SAVE TRANSACTION InsertIntoSponsorships;
        SET @rollBackPointSponsorships = 1;

        COMMIT TRANSACTION;

        INSERT INTO Logs (Action) VALUES ('InsertSponsorshipGrade5 succeeded.');
    END TRY
    BEGIN CATCH
        IF @@TRANCOUNT > 0
            BEGIN
                IF @rollBackPointSponsorships = 1
                    BEGIN
                        ROLLBACK TRANSACTION InsertIntoSponsorships;
                        PRINT ERROR_MESSAGE();
                        COMMIT TRANSACTION;
                    END
                ELSE IF @rollBackPointSponsors = 1
                    BEGIN
                        ROLLBACK TRANSACTION InsertIntoSponsors;
                        PRINT ERROR_MESSAGE();
                        COMMIT TRANSACTION;
                    END
                ELSE IF @rollBackPointAthletes = 1
                    BEGIN
                        ROLLBACK TRANSACTION InsertIntoAthletes;
                        PRINT ERROR_MESSAGE();
                        COMMIT TRANSACTION;
                    END
                ELSE
                    BEGIN
                        ROLLBACK TRANSACTION;
                        PRINT ERROR_MESSAGE();
                        COMMIT TRANSACTION;
                    END
            END
        ELSE
            BEGIN
                PRINT ERROR_MESSAGE();
            END
        
        INSERT INTO Logs (Action, ErrorMessage)
        VALUES ('InsertSponsorshipGrade5 failed', ERROR_MESSAGE());
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
EXEC InsertSponsorshipGrade5 
    @AthleteName = 'Cristiano Ronaldo', 
    @SponsorName = 'Nike', 
    @StartDate = '2023-01-01', 
    @EndDate = '2024-01-01';

-- 2. Error scenario: 
--      repeat the same name for the sponsor 
--      (Sponsors table has a unique constraint on name)
EXEC InsertSponsorshipGrade5 
    @AthleteName = 'Lionel Messi', 
    @SponsorName = 'Nike', 
    @StartDate = '2023-01-01', 
    @EndDate = '2024-01-01';