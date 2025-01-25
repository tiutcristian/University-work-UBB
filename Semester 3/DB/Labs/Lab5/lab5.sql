DROP TABLE IF EXISTS Tc
DROP TABLE IF EXISTS Tb
DROP TABLE IF EXISTS Ta

CREATE TABLE Ta (
    aid INT PRIMARY KEY,
    a2 INT UNIQUE,
    a3 INT
)

CREATE TABLE Tb (
    bid INT PRIMARY KEY,
    b2 INT
)

CREATE TABLE Tc (
    cid INT PRIMARY KEY,
    aid INT REFERENCES Ta(aid),
    bid INT REFERENCES Tb(bid),
    c3 INT
)


-- a)
-- Clustered Index Scan
SELECT * FROM Ta ORDER BY aid

-- Clustered Index seek
SELECT * FROM Ta WHERE aid = 10

-- Nonclustered index scan
SELECT a2 FROM Ta ORDER BY a2

-- Nonclustered index seek
SELECT a2 FROM Ta WHERE a2 > 10

-- key lookup
SELECT * FROM Ta WHERE a2 = 10



-- b)
DROP INDEX IF EXISTS idx_b2 ON Tb

SELECT * FROM Tb WHERE b2 = 10

-- Before: Clustered Index Scan
CREATE INDEX idx_b2 ON Tb(b2)
-- After: Clustered Index Seek


-- c)
GO
CREATE OR ALTER VIEW TcViewV2 AS
    SELECT Ta.aid, Tc.cid
    FROM Ta
    JOIN Tc ON Ta.aid = Tc.aid
    WHERE Ta.a2 = 10
GO

SELECT * FROM TcViewV2

-- Before: Clustered Index Scan(TC) + Clustered Index Seek(Ta)
CREATE INDEX idx_Tc_aid ON Tc(aid)
-- After: Clustered Index Seek(TC) + Clustered Index Seek(Ta)