CREATE TABLE Logs (
    LogID INT PRIMARY KEY IDENTITY(1,1),
    LogDate DATETIME DEFAULT GETDATE(),
    [Action] NVARCHAR(MAX),
    ErrorMessage NVARCHAR(MAX)
);