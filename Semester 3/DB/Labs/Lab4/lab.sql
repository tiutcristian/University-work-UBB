CREATE OR ALTER PROCEDURE insertRowIntoTable(@tableName VARCHAR(255), @row INT) AS 
	DECLARE @ColumnName NVARCHAR(128);
    DECLARE @DataType NVARCHAR(128);
	DECLARE @sql NVARCHAR(255);
	DECLARE @columnNames NVARCHAR(255);
	DECLARE @columnValues NVARCHAR(255);
    DECLARE ColumnCursor CURSOR SCROLL FOR
    SELECT COLUMN_NAME, DATA_TYPE
    FROM INFORMATION_SCHEMA.COLUMNS
    WHERE TABLE_NAME = @TableName;

	SET @columnNames = '';
	SET @columnValues = '';

    OPEN ColumnCursor;
    FETCH NEXT FROM ColumnCursor INTO @ColumnName, @DataType;
    WHILE @@FETCH_STATUS = 0 BEGIN
		SET @columnNames = @columnNames + @ColumnName + ',';
		
		IF @DataType = 'int' BEGIN
			SET @columnValues = @columnValues + CAST(@row AS VARCHAR(255)) + ',' -- row number
		END
		ELSE IF @DataType = 'varchar' BEGIN
			SET @columnValues = @columnValues + '''' + 'row_' + CAST(@row AS VARCHAR(255)) + ''',' -- "row_" + row number
		END
		ELSE IF @DataType = 'date' BEGIN
			SET @columnValues = @columnValues + 'GETDATE(),' -- current date
        END

		FETCH NEXT FROM ColumnCursor INTO @ColumnName, @DataType;
	END

	SET @columnNames = LEFT(@columnNames, LEN(@columnNames) - 1); -- remove last comma
	SET @columnValues = LEFT(@columnValues, LEN(@columnValues) - 1); -- remove last comma
	SET @sql = 'INSERT INTO ' + @tableName + '(' + @columnNames + ') VALUES (' + @columnValues + ')';
	IF (OBJECTPROPERTY(OBJECT_ID(@tableName), 'TableHasIdentity') = 1) BEGIN -- if table has identity column, enable identity insert
		SET @sql = 'SET IDENTITY_INSERT ' + @tableName + ' ON;' + @sql + ';SET IDENTITY_INSERT ' + @tableName + ' OFF;'
	END
	EXEC (@sql)

	CLOSE ColumnCursor;
	DEALLOCATE ColumnCursor;
GO


CREATE OR ALTER PROCEDURE populateTable (@tableName VARCHAR(255), @rows INT) AS
	DECLARE @i INT
	SET @i = 1
	WHILE @i <= @rows BEGIN
		EXEC insertRowIntoTable @tableName, @i
		SET @i = @i + 1
	END
GO


CREATE OR ALTER PROCEDURE deleteFromTable(@tableName VARCHAR(255)) AS
	EXEC ('DELETE FROM ' + @tableName)
GO


CREATE OR ALTER PROCEDURE addToTables (@tableName VARCHAR(255)) AS
	INSERT INTO Tables(Name) Values (@tableName);
GO


CREATE OR ALTER PROCEDURE addToViews(@viewName VARCHAR(255)) AS 
	INSERT INTO Views(Name) Values (@viewName);
GO


CREATE OR ALTER PROCEDURE addToTests(@testName VARCHAR(255)) AS 
	INSERT INTO Tests(Name) Values (@testName);
GO


CREATE OR ALTER PROCEDURE connectTableToTest(@tableName VARCHAR(255), @testName VARCHAR(255), @rows INT, @pos INT) AS
	DECLARE @tableId int
	DECLARE @testId int
	SET @tableId = (SELECT TableID FROM Tables WHERE Name=@tableName)
	SET @testId = (SELECT TestID FROM Tests WHERE Name=@testName)
	INSERT INTO TestTables VALUES(@testId, @tableId, @rows, @pos);
GO	


CREATE OR ALTER PROCEDURE connectViewToTest(@viewName VARCHAR(255), @testName VARCHAR(255)) AS
	DECLARE @viewId int
	DECLARE @testId int
	SET @viewId = (SELECT ViewID FROM Views WHERE Name=@viewName)
	SET @testId = (SELECT TestID FROM Tests WHERE Name=@testName)
	INSERT INTO TestViews  VALUES(@testId, @viewId);
GO


CREATE OR ALTER PROCEDURE runTest(@testName VARCHAR(255), @description VARCHAR(255)) AS
	SET NOCOUNT ON

	DECLARE @testStartTime DATETIME2
	DECLARE @testRunId INT
	DECLARE @tableId INT
	DECLARE @table VARCHAR(255)
	DECLARE @rows INT
	DECLARE @pos INT
	DECLARE @command VARCHAR(255)
	DECLARE @tableInsertStartTime DATETIME2
	DECLARE @tableInsertEndTime DATETIME2
	DECLARE @testId INT
	DECLARE @view VARCHAR(255)
	DECLARE @viewId INT
	DECLARE @viewStartTime DATETIME2
	DECLARE @viewEndTime DATETIME2
	
	SET @testId = (SELECT TestId FROM Tests T WHERE T.Name = @testName)
	
	DECLARE tableCursor CURSOR SCROLL FOR 
		SELECT T1.Name, T1.TableId, T2.NoOfRows, T2.Position
		FROM Tables T1 INNER JOIN TestTables T2 ON T1.TableID = T2.TableID
		WHERE T2.TestID = @testId
		ORDER BY T2.Position DESC
	
	DECLARE viewCursor CURSOR SCROLL FOR 
		SELECT V.Name, V.ViewId
		FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID 
		WHERE TV.TestID = @testId
	
	
	SET @testStartTime = sysdatetime()
	
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES(@description, @testStartTime, @testStartTime)
	SET @testRunId = SCOPE_IDENTITY()
	
	OPEN tableCursor
	FETCH FIRST FROM tableCursor INTO @table, @tableId, @rows, @pos
	WHILE @@FETCH_STATUS = 0 BEGIN
		EXEC deleteFromTable @table
		FETCH tableCursor INTO @table, @tableId, @rows, @pos
	END
	FETCH LAST FROM tableCursor INTO @table, @tableId, @rows, @pos
	WHILE @@FETCH_STATUS = 0 BEGIN
		SET @tableInsertStartTime = sysdatetime()
		EXEC populateTable @table, @rows
		SET @tableInsertEndTime = sysdatetime()
		INSERT INTO TestRunTables VALUES(@testRunId, @tableId, @tableInsertStartTime, @tableInsertEndTime)
		FETCH PRIOR FROM tableCursor INTO @table, @tableId, @rows, @pos
	END
	CLOSE tableCursor
	DEALLOCATE tableCursor 
	
	OPEN viewCursor
	FETCH viewCursor INTO @view, @viewId
	WHILE @@FETCH_STATUS = 0 BEGIN
		SET @viewStartTime = sysdatetime()
		EXEC ('SELECT * FROM ' + @view)
		SET @viewEndTime = sysdatetime()
		INSERT INTO TestRunViews VALUES(@testRunID, @viewId, @viewStartTime, @viewEndTime)
		FETCH viewCursor INTO @view, @viewId	
	END
	CLOSE viewCursor 
	DEALLOCATE viewCursor

	UPDATE TestRuns 
	SET EndAt = sysdatetime()
	WHERE TestRunID = @testRunId;
GO


CREATE VIEW simpleView AS
	SELECT * FROM Coaches WHERE id < 10;
GO


CREATE VIEW coachTeamView AS
	SELECT C.name AS CoachName, T.name AS TeamName
	FROM Coaches C
	JOIN Teams T ON C.id = T.coach_id
GO


CREATE VIEW coachAthleteCountView AS
	SELECT C.name AS CoachName, COUNT(A.id) AS AthleteCount
	FROM Coaches C
	JOIN Teams T ON C.id = T.coach_id
	JOIN Athletes A ON T.id = A.team_id
	GROUP BY C.name
GO



-- SETUP
EXEC addToTests 'Test 1';

EXEC addToTables 'Sponsors';
EXEC addToTables 'Sponsorships';
EXEC addToTables 'Athletes';
EXEC addToTables 'Teams';
EXEC addToTables 'Coaches';

EXEC addToViews 'simpleView';
EXEC addToViews 'coachTeamView';
EXEC addToViews 'coachAthleteCountView';

EXEC connectTableToTest 'Coaches', 'Test 1', 100, 1;
EXEC connectTableToTest 'Teams', 'Test 1', 100, 2;
EXEC connectTableToTest 'Athletes', 'Test 1', 100, 3;
EXEC connectTableToTest 'Sponsors', 'Test 1', 100, 4;
EXEC connectTableToTest 'Sponsorships', 'Test 1', 100, 5;

EXEC connectViewToTest 'simpleView', 'Test 1';
EXEC connectViewToTest 'coachTeamView', 'Test 1';
EXEC connectViewToTest 'coachAthleteCountView', 'Test 1';


-- RUN
EXEC runTest 'Test 1', 'descriere test 1';
SELECT * FROM TestRuns;
DELETE FROM TestRuns;

SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;