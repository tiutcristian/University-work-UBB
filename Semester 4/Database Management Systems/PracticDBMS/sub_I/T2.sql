USE Sub
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ

BEGIN TRAN
UPDATE Project
SET Name='Green Campus'
WHERE ProjectID=7
COMMIT TRAN
