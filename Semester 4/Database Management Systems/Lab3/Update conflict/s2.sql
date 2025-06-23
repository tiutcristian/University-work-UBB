USE [Triathlon]

-- setup
SET TRANSACTION ISOLATION LEVEL SNAPSHOT;

BEGIN TRAN
	Select * from Athletes where name = 'Messi'
	Waitfor delay '00:00:10'
	update Athletes set email='Mail nou transaction 2' where name = 'Messi'
COMMIT TRAN