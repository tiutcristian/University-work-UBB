# Seminar 4 
## Table of Contents
- [Functions](#functions)
- [Views](#views)
- [System Catalog](#system-catalog)
- [Triggers](#triggers)
- [MERGE Statement](#merge-statement)
- [Examples](#examples)



## Functions
a. **scalar** --> select, where, having  
b. **inline table-valued**    
c. **multi-statement table-valued**  

<i>OBS.: These can be used in a FROM clause.</i>

Example a.
```sql
CREATE FUNCTION ufNoMissions(@location VARCHAR(100))
RETURNS INT AS
BEGIN
    DECLARE @no INT

    SELECT @no = COUNT(*) 
    FROM Missions M
    WHERE M.Location = @location

    RETURN @no
END
GO
```

Example b.
```sql
CREATE FUNCTION ufNameMissions(@location VARCHAR(100))
RETURNS TABLE AS RETURN
    SELECT M.Name
    FROM Missions M
    WHERE M.Location = @location
GO
```

Using the function:
```sql
PRINT dbo.ufNoMissions('Clooj')
```

```sql
SELECT * 
FROM dbo.ufNameMissions('Clooj')
```

## Views

```sql
CREATE VIEW viewTasks AS
    SELECT *
    FROM Missions M 
    JOIN Tasks T ON M.MissionID = T.MissionID
GO
```

Using the view:
```sql
SELECT *
FROM viewTasks
```

## System Catalog

sys.objects  

__type
- U: User table
- PK: Primary key
- F: Foreign key
- P: Stored procedure
- D: Default constraint
- FN: Scalar function
- IF: Inline table-valued function
- TF: Multi-statement table-valued function

sys.indexes
sys.parameters
sys.columns
sys.sql_modules

```sql
SELECT *
FROM sys.objects o
JOIN sys.parameters p ON o.object_id = p.object_id
```

## Triggers
- special type of stored procedure
- automatically executed when a specific event occurs (when another SQL statement is executed)
- cannot be executed directly
- DDL (create, drop, alter) or DML (insert, update, delete)
- inserted and deleted tables
- the moment the trigger is executed:
    - FOR, AFTER
    - INSTEAD OF
- multiple triggers for the same event and the same time are executed in random order
---
**General syntax:**
```sql
CREATE TRIGGER trigger_name
ON table_name
FOR | AFTER | INSTEAD OF {INSERT, UPDATE, DELETE}
AS
BEGIN
    -- code
END
GO
```
---
```sql
SET NOCOUNT ON; -- suppress the "xx rows affected" message
                -- by default, it's OFF
```
---
Change data capture
- uses triggers to capture changes
- data is monitored automatically
- enabling/disabling CDC
    - `sys.sp_cdc_enable_db`
    - `sys.sp_cdc_enable_table` - table given as parameter
    - `sys.sp_cdc_disable_db`
    - `sys.sp_cdc_disable_table` - table given as parameter

## MERGE Statement
```sql
MERGE Grades 
USING (
    SELECT 
        MIN(gid) AS gid, 
        course, 
        student, 
        MAX(exam_room) AS exam_room,
        MAX(grade) AS grade
        MAX(grade_date) AS grade_date
    FROM Grades
    GROUP BY student, course
) AS mergedData 
ON Grades.gid = mergedData.gid
WHEN MATCHED THEN
    UPDATE SET 
        Grades.course = mergedData.course,
        Grades.student = mergedData.student,
        Grades.exam_room = mergedData.exam_room,
        Grades.grade = mergedData.grade,
        Grades.grade_date = mergedData.grade_date
WHEN NOT MATCHED BY SOURCE THEN
    DELETE;
GO
```

## Examples
- Multi-statement table-valued function

```sql
CREATE FUNCTION ufMissionsFilteredByLocation (@location VARCHAR(100))
RETURNS @FilteredTable TABLE(
    mid INT,
    missionName VARCHAR(100)
) AS
BEGIN
    INSERT INTO @FilteredTable
    SELECT mid, name
    FROM Missions
    WHERE Missions.location = @location
    IF @@ROWCOUNT = 0
        INSERT INTO @FilteredTable
        VALUES (0, 'No missions found')
    RETURN
END
GO

--select the created table
SELECT *
FROM dbo.ufMissionsFilteredByLocation('Clooj')
```
---
- Triggers

```sql
CREATE TRIGGER WhenSellingABook
ON Books 
FOR INSERT
AS
BEGIN
    INSERT INTO BooksSoldLog(book_title, log_date, quantity)
    SELECT title, GETDATE(), quantity
    FROM inserted
END
GO

-- execute the trigger
INSERT INTO Books (bid, title, authors, noPages, quantity)
VALUES (15, 'The Book', 'The Author', 100, 10)
```
---
```sql
CREATE TRIGGER WhenSomeonesBuysABook
ON Books 
FOR DELETE
AS
BEGIN
    INSERT INTO BooksBoughtLog(book_title, log_date, quantity)
    SELECT title, GETDATE(), quantity
    FROM deleted
END
GO

-- execute the trigger
DELETE FROM Books
WHERE bid = 15
```
---
```sql
CREATE TRIGGER WhenSomeonesChangesABook
ON Books 
FOR UPDATE
AS
BEGIN 
    SET NOCOUNT ON;

    INSERT INTO BooksBoughtLog(book_title, log_date, quantity)
    SELECT i.title, GETDATE(), i.quantity - d.quantity
    FROM deleted d INNER JOIN inserted i ON d.bid = i.bid
    WHERE i.quantity > d.quantity

    INSERT INTO BooksSoldLog(book_title, log_date, quantity)
    SELECT i.title, GETDATE(), d.quantity - i.quantity
    FROM deleted d INNER JOIN inserted i ON d.bid = i.bid
    WHERE i.quantity < d.quantity
END
GO

-- execute the trigger
UPDATE Books
SET quantity = quantity - 5
WHERE bid = 15
```
---
Delete trigger
```sql
DROP TRIGGER WhenSomeonesChangesABook
```