# Seminar 2 - Data manipulation language (DML)
- Select
- Insert
- Update
- Delete

## 1. Select
```sql
SELECT [DISTINCT] [TOP N] column1, column2, ...
FROM Table1 t1, Table2 t2, ...
WHERE condition
[GROUP BY column1]
[HAVING group-qualification]
[ORDER BY column1]
```

```sql
SELECT  Over18 = S.age - 18, 
        S.age * 2 AS DoubleAge, 
        S.weight / (S.height * S.height) BMI
FROM Students S
WHERE S.name LIKE '_%'
```

### 1.1. Set operators

- `UNION` / `UNION ALL` (UNION removes duplicates, UNION ALL does not)
```sql
SELECT column1, column2, ...
FROM Table1

UNION

SELECT column1, column2, ...
FROM Table2
```

- `INTERSECT`
```sql
SELECT T.spyId
FROM Tasks T, Missions M
WHERE T.missionId = M.missionId AND M.location = 'Online'

INTERSECT

SELECT T.spyId
FROM Tasks T, Missions M
WHERE T.missionId = M.missionId AND M.location <> 'Online'
```

- `EXCEPT`
```sql
SELECT T.spyId
FROM Tasks T, Missions M
WHERE T.missionId = M.missionId AND M.location = 'Online'

EXCEPT

SELECT T.spyId
FROM Tasks T, Missions M
WHERE T.missionId = M.missionId AND M.location <> 'Online'
```

### 1.2. Nested queries
Find the real names of the spies who have not been assigned a task in mission 100

a. Using `NOT IN`
```sql
SELECT S.realName
FROM Spies S
WHERE S.spyId NOT IN (
    SELECT T.spyId
    FROM Tasks T
    WHERE T.missionId = 100
)
```

b. Using `NOT EXISTS`
```sql
SELECT S.realName
FROM Spies S
WHERE NOT EXISTS (
    SELECT T.spyId
    FROM Tasks T
    WHERE T.missionId = 100 AND T.spyId = S.spyId
)
```

Find the real names of the spies with age greater than some spy named "John"

```sql
SELECT S.realName
FROM Spies S
WHERE S.age > ANY (
    SELECT S2.age
    FROM Spies S2
    WHERE S2.realName = 'John'
)
```

Find the real names of the spies with age greater than all spies named "John"

```sql
SELECT S.realName
FROM Spies S
WHERE S.age > ALL (
    SELECT S2.age
    FROM Spies S2
    WHERE S2.realName = 'John'
)
```

Equivalent keywords:  
- ALL <=> MAX  
- ANY <=> MIN  
- NOT IN <=> EXCEPT  
- IN <=> INTERSECT  
- expr <> ALL (subquery) <=> expr NOT IN (subquery)
- expr = ANY (subquery) <=> expr IN (subquery)

### 1.3. Joins
- `[INNER] JOIN` = join only the rows that have a match in both tables
- `LEFT JOIN` = join all rows from the left table and the matched rows from the right table
- `RIGHT JOIN` = join all rows from the right table and the matched rows from the left table
- `FULL JOIN` = join all rows from both tables

```sql
SELECT column1, column2, ...
FROM Table1 T1 
JOIN Table2 T2 ON T1.column = T2.column
```

### 1.4 Aggregate functions
After `GROUP BY`, you can only use <b>aggregate functions</b> in the select clause:
- `COUNT`
- `SUM`
- `AVG`
- `MIN`
- `MAX`

Obs.: `HAVING` is like `WHERE` but for groups

### 1.5. Subqueries in `FROM` clause

e.g. Find all the players who have won at least one singles match
```sql
SELECT *
FROM (
    SELECT *
    FROM Player P
    WHERE P.id in (
        SELECT m.winnerId
        FROM SinglesMatch m
    )
) as P2
WHERE P2.numberOfPoints > 5000
```