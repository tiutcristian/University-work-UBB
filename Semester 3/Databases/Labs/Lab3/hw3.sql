CREATE OR ALTER PROCEDURE sp_ModifyColumn
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128),
    @newType NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + ' ALTER COLUMN ' + @columnName + ' ' + @newType

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_AddColumn
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128),
    @columnType NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + ' ADD ' + @columnName + ' ' + @columnType

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_RemoveColumn
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + ' DROP COLUMN ' + @columnName

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_AddDefaultConstraint
    @tableName NVARCHAR(128),
    @defaultValue NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' ADD CONSTRAINT default_' + @columnName +
    ' DEFAULT ' + @defaultValue + 
    ' FOR ' + @columnName

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_RemoveDefaultConstraint
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' DROP CONSTRAINT default_' + @columnName

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_AddPrimaryKey
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' ADD CONSTRAINT PK__' + @tableName + '__' + @columnName +
    ' PRIMARY KEY (' + @columnName + ')'

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_RemovePrimaryKey
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' DROP CONSTRAINT PK__' + @tableName + '__' + @columnName

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_AddCandidateKey
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' ADD CONSTRAINT CK__' + @tableName + '__' + @columnName +
    ' UNIQUE (' + @columnName + ')'

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_RemoveCandidateKey
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' DROP CONSTRAINT CK__' + @tableName + '__' + @columnName

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_AddForeignKey
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128),
    @refTableName NVARCHAR(128),
    @refColumnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' ADD CONSTRAINT FK__' + @tableName + '__' + @columnName +
    ' FOREIGN KEY (' + @columnName + ') REFERENCES ' + @refTableName + '(' + @refColumnName + ')'

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_RemoveForeignKey
    @tableName NVARCHAR(128),
    @columnName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'ALTER TABLE ' + @tableName + 
    ' DROP CONSTRAINT FK__' + @tableName + '__' + @columnName

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_CreateTable
    @tableName NVARCHAR(128),
    @columns NVARCHAR(MAX)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'CREATE TABLE ' + @tableName + ' (' + @columns + ')'

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE sp_DropTable
    @tableName NVARCHAR(128)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX)

    SET @sql = 'DROP TABLE ' + @tableName

    EXEC sp_executesql @sql
END
GO

--------------------------------------------

CREATE TABLE SchemaVersion (
    Id INT PRIMARY KEY CHECK (Id = 1),
    Version INT NOT NULL
);
INSERT INTO SchemaVersion (Id, Version) VALUES (1, 1);
GO

--------------------------------------------

CREATE TABLE VersionToScriptMapping (
    prev_version INT,
    target_version INT NOT NULL,
    Script NVARCHAR(MAX) NOT NULL,
    PRIMARY KEY (prev_version, target_version)
);

INSERT INTO VersionToScriptMapping VALUES (1, 2, 'sp_CreateTable ''NewTable'', ' +
    '''id INT NOT NULL, ' + 
    'col NVARCHAR(128), ' +
    'def_col INT, ' +
    'cand_col INT NOT NULL, ' +
    'foreign_col INT NOT NULL'''
);
INSERT INTO VersionToScriptMapping VALUES (2, 3, 'sp_ModifyColumn ''NewTable'', ''col'', ''INT''');
INSERT INTO VersionToScriptMapping VALUES (3, 4, 'sp_AddColumn ''NewTable'', ''new_col'', ''INT''');
INSERT INTO VersionToScriptMapping VALUES (4, 5, 'sp_AddDefaultConstraint ''NewTable'', ''0'', ''def_col''');
INSERT INTO VersionToScriptMapping VALUES (5, 6, 'sp_AddPrimaryKey ''NewTable'', ''id''');
INSERT INTO VersionToScriptMapping VALUES (6, 7, 'sp_AddCandidateKey ''NewTable'', ''cand_col''');
INSERT INTO VersionToScriptMapping VALUES (7, 8, 'sp_AddForeignKey ''NewTable'', ''foreign_col'', ''Teams'', ''id''');

INSERT INTO VersionToScriptMapping VALUES (2, 1, 'sp_DropTable ''NewTable''');
INSERT INTO VersionToScriptMapping VALUES (3, 2, 'sp_ModifyColumn ''NewTable'', ''col'', ''NVARCHAR(128)''');
INSERT INTO VersionToScriptMapping VALUES (4, 3, 'sp_RemoveColumn ''NewTable'', ''new_col''');
INSERT INTO VersionToScriptMapping VALUES (5, 4, 'sp_RemoveDefaultConstraint ''NewTable'', ''def_col''');
INSERT INTO VersionToScriptMapping VALUES (6, 5, 'sp_RemovePrimaryKey ''NewTable'', ''id''');
INSERT INTO VersionToScriptMapping VALUES (7, 6, 'sp_RemoveCandidateKey ''NewTable'', ''cand_col''');
INSERT INTO VersionToScriptMapping VALUES (8, 7, 'sp_RemoveForeignKey ''NewTable'', ''foreign_col''');
GO

--------------------------------------------

CREATE OR ALTER PROCEDURE MigrateToVersion
    @TargetVersion INT
AS
BEGIN
    DECLARE @CurrentVersion INT;

    SELECT @CurrentVersion = Version FROM SchemaVersion WHERE Id = 1;

    WHILE @CurrentVersion < @TargetVersion
    BEGIN
        DECLARE @Script NVARCHAR(MAX);

        SELECT @Script = Script 
        FROM VersionToScriptMapping 
        WHERE prev_version = @CurrentVersion AND target_version = @CurrentVersion + 1;

        PRINT @Script; -- for debugging purposes
    
        EXEC sp_executesql @Script;

        SET @CurrentVersion = @CurrentVersion + 1;

        UPDATE SchemaVersion SET Version = @CurrentVersion;
    END

    WHILE @CurrentVersion > @TargetVersion
    BEGIN
        DECLARE @Script2 NVARCHAR(MAX);

        SELECT @Script2 = Script
        FROM VersionToScriptMapping
        WHERE prev_version = @CurrentVersion AND target_version = @CurrentVersion - 1;

        PRINT @Script2; -- for debugging purposes
        
        EXEC sp_executesql @Script2;

        SET @CurrentVersion = @CurrentVersion - 1;
        
        UPDATE SchemaVersion SET Version = @CurrentVersion;
    END
END;

--------------------------------------------

-- Test
EXEC MigrateToVersion @TargetVersion = 1;
EXEC MigrateToVersion @TargetVersion = 2;
EXEC MigrateToVersion @TargetVersion = 3;
EXEC MigrateToVersion @TargetVersion = 4;
EXEC MigrateToVersion @TargetVersion = 5;
EXEC MigrateToVersion @TargetVersion = 6;
EXEC MigrateToVersion @TargetVersion = 7;
EXEC MigrateToVersion @TargetVersion = 8;

--------------------------------------------

-- V1 = no table
-- V2 = table is created, col is VARCHAR
-- V3 = col is INT, no new_col
-- V4 = new_col is added, def_col has no default constraint
-- V5 = def_col has default constraint, no primary key
-- V6 = primary key is added, no candidate key
-- V7 = candidate key is added, no foreign key
-- V8 = foreign key is added