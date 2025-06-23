USE [Triathlon]

-- setup
DELETE FROM Athletes
INSERT INTO Athletes(name, email) VALUES ('Messi','Mail')
SELECT * FROM Athletes

-- act
waitfor delay '00:00:10'
BEGIN TRAN
	update Athletes set email='Mail nou transaction 1' where name = 'Messi'
	waitfor delay '00:00:10'
COMMIT TRAN