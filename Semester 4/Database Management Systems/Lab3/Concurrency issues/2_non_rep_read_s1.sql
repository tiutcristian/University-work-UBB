USE [Triathlon]

-- setup
DELETE FROM Athletes
INSERT INTO Athletes(name, email) VALUES ('Messi','Mail initial')
SELECT * FROM Athletes

-- act
BEGIN TRAN
WAITFOR DELAY '00:00:05'
UPDATE Athletes SET email='Mail nou' WHERE name = 'Messi'
COMMIT TRAN