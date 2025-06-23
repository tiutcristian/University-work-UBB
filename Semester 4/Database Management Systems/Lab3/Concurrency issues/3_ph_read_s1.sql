USE [Triathlon]

-- setup
DELETE FROM Athletes
SELECT * FROM Athletes

-- act
BEGIN TRAN
WAITFOR DELAY '00:00:04'
INSERT INTO Athletes(name, email) VALUES ('Messi','Mail')
COMMIT TRAN