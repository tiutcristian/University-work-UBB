CREATE DATABASE labtest;



CREATE TABLE testare(
    id INT PRIMARY KEY,
    A int,
    B int,
    C int,
    D int
)



INSERT INTO testare(id, A, B, C, D) 
VALUES(29,10,28,8,3)



select * FROM testare



select T1.id, COUNT(*) as N_rows
from testare T1
    inner join testare T2 on T1.id = T2.id
    LEFT JOIN testare T3 on T2.id = T3.B
WHERE T1.C > 7
GROUP BY T1.id
HAVING COUNT(*) > 2



SELECT t1.B, SUM(t1.D) as E
FROM testare t1
GROUP BY t1.B

UNION ALL

SELECT t2.B, COUNT(t2.C) as E
FROM testare t2
GROUP BY t2.B


GO
CREATE OR ALTER TRIGGER insert_trigger
ON testare
FOR INSERT
AS
    DECLARE @total INT

    SELECT @total = SUM(i.C - i.D)
    FROM inserted i

    PRINT @total
GO

INSERT INTO testare(id, A, B, C, D) VALUES
(30, 11, 28, 9, 3),
(31, 12, 30, 9, 4)