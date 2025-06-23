USE PracticDBMS

-- act
begin tran
update StudentMember set name='Nume nou transaction 1' where id = 1
waitfor delay '00:00:05'
update ProjectTeam set name='Nume nou transaction 1' where id = 1
commit tran