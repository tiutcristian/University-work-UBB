USE [Triathlon]

-- setup
DELETE FROM Athletes
INSERT INTO Athletes(name, email) VALUES ('Messi','Mail')
SELECT * FROM Athletes
DELETE FROM Sponsors
INSERT INTO Sponsors(name, country) VALUES ('Nike','USA')
SELECT * FROM Sponsors

-- act
begin tran
update Athletes set email='Mail nou transaction 1' where name = 'Messi'
waitfor delay '00:00:05'
update Sponsors set country='USA nou transaction 1' where name = 'Nike'
commit tran