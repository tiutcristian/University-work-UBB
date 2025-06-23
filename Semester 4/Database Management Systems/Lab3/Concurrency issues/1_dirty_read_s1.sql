USE [Triathlon]

-- setup
DELETE FROM Athletes
INSERT INTO Athletes(name, email) VALUES ('Messi','Mail initial')
SELECT * FROM Athletes

-- act
BEGIN TRANSACTION
UPDATE Athletes SET email='Mail nou' WHERE name = 'Messi'
WAITFOR DELAY '00:00:10'
ROLLBACK TRANSACTION