# Seminar 1

## There are 2 types of representations:
1. Entity-Relationship Diagrams - the one with shapes
2. Relational Schemas - class-like

Mapping between them on paper from seminar 1.

To identify the relationships between entities, we need to look at the relationship from both sides: 
- A owns a/more B
- B is owned by a/more A

## SQL - Data Definition Languge (DDL):
- 3 operations:
    - `CREATE`
    - `DROP`
    - `ALTER`

- `VARCHAR` vs `CHAR`
    - `VARCHAR`: variable length
    - `CHAR`: fixed length

- other types of data:
    - `INT`, `TINYINT` (1 byte), `SMALLINT` (2 bytes), `BIGINT`, `FLOAT`
    - `DECIMAL(total_digits, decimal_digits)`
    - `BOOLEAN`
    - `DATE`, `TIME`, `DATETIME`, `TIMESTAMP`
    - `MONEY`
    - `TEXT`
    - `IMAGE`

- Altering tables:
    ```sql
    ALTER TABLE Students
    ADD COLUMN Age INT;
    ```
    ```sql
    ALTER TABLE Students
    ALTER COLUMN Age TINYINT;
    ```
    ```sql
    ALTER TABLE Students
    DROP COLUMN Age;
    ```

- Primary key with identity:
    ```sql
    StudentID INT PRIMARY KEY IDENTITY(<starting_number>,<step>)
    ```

- Foreign key actions (on `DELETE`/`UPDATE`):
    - `NO ACTION` - the update / delete is not allowed if it violates the 
                    specified integrity constraint (default option);
    - `CASCADE` - the update / delete is not allowed if it violates 
                the specified integrity constraint (default option);
    - `SET NULL` - the foreign key column value is replaced by null 
                (only if it's nullable);
    - `SET DEFAULT` - the foreign key column value is replaced by its default 
                    value (specified with DEFAULT); if a column is nullable and 
                    doesn't have a DEFAULT definition, null will be considered
                    as the default value for the column.
    ```sql
    FOREIGN KEY (StudentID) REFERENCES Students(StudentID) 
    ON DELETE CASCADE
    ON UPDATE NO ACTION
    ```