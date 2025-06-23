USE PracticDBMS
-- act - initially
begin tran
update ProjectTeam set name='Nume nou transaction 2' where id = 1
waitfor delay '00:00:05'
update StudentMember set name='Nume nou transaction 2' where id = 1
commit tran

-- reset
update ProjectTeam set name='Nume initial' where id = 1
update StudentMember set name='Nume initial' where id = 1

-- act - solution
begin tran
update StudentMember set name='Nume nou transaction 2' where id = 1
waitfor delay '00:00:05'
update ProjectTeam set name='Nume nou transaction 2' where id = 1
commit tran