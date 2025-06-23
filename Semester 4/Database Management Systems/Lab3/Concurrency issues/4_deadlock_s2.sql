USE [Triathlon]
-- act - initially
begin tran
update Sponsors set country='USA nou transaction 2' where name = 'Nike'
waitfor delay '00:00:05'
update Athletes set email='Mail nou transaction 2' where name = 'Messi'
commit tran

-- act - solution
begin tran
update Athletes set email='Mail nou transaction 2' where name = 'Messi'
waitfor delay '00:00:05'
update Sponsors set country='USA nou transaction 2' where name = 'Nike'
commit tran