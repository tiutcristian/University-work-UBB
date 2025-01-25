# Seminar 3

## Stored procedures
-  Contains a group of Transact-SQL statements.

Structure of a stored procedure:
```sql
CREATE PROCEDURE name_of_procedure
    @parameter1 INT,            -- input parameter
    @parameter2 VARCHAR(50),    -- input parameter
    @parameter3 DATE OUTPUT     -- output parameter
    @parameter4 INT OUTPUT      -- output parameter
AS
BEGIN
    SELECT @parameter3 = GETDATE(), @parameter4 = @parameter1 + @parameter2
    FROM table_name
    WHERE column_name = @parameter1;
END;
```
\
Execute a stored procedure:
```sql
EXEC name_of_procedure 1, 'string', @parameter3 OUTPUT, @parameter4 OUTPUT;
```
\
Dynamic execution of a stored procedure (security risk):
```sql
SET @sql = 'ALTER TABLE ' + @tableName + ' ALTER COLUMN ' + @columnName + ' ' + @newType
EXEC sp_executesql @sql
```
 
## Variables
Declare a variable:
```sql
DECLARE @variable1 INT;
```

\
Assign a value to a variable:
```sql
SET @variable1 = 1;
```


## Global variables
-  Can be accessed from any stored procedure or batch within the connection.
- Are prefixed with `@@`.


## Output Clause
- `INSERTED` and `DELETED` tables are used to return the values of columns in the affected rows.  
- In case of UPDATE, we first delete the row and then insert the new row.

```sql
UPDATE table_name
SET column_name = 'new_value'
OUTPUT 
    INSERTED.column_name AS new_column_name, 
    DELETED.column_name AS old_column_name;
```


## `SELECT INTO` statement
```sql
SELECT column1, column2
INTO new_table
FROM table_name;
```


## Cursors
-  Used to <i>iterate</i> through a result set.
-  The cursor is always associated with a `SELECT` statement.
-  The cursor is:
    - opened
    - fetched
    - closed
- Fetch options:
    - `NEXT`
    - `PRIOR`
    - `FIRST`
    - `LAST`
    - `ABSOLUTE n` = nth from the beginning
    - `RELATIVE n` = nth from the current position
- Like the classic `for` loop in programming languages.
```sql
DECLARE cursor_name CURSOR FOR
    SELECT column1, column2
    FROM table_name

OPEN cursor_name

FETCH cursor_name INTO @variable1, @variable2

WHILE @@FETCH_STATUS = 0 BEGIN
    -- do something
    FETCH cursor_name INTO @variable1, @variable2
END

CLOSE cursor_name

DEALLOCATE cursor_name
```