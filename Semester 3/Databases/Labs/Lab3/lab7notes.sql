CREATE PROCEDURE sp_ProcessOverduFees AS
BEGIN

    DECLARE @bookId INT, @memberId INT, @rentalDate DATE, @dueDate DATE

    DECLARE overdueRentals CURSOR FOR
        SELECT bookId, memberId, rentalDate, dueDate
        FROM Rentals
        WHERE dueDate < GETDATE()

    OPEN overdueRentals
    FETCH NEXT FROM overdueRentals INTO @bookId, @memberId, @rentalDate, @dueDate

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @daysOverdue = DATEDIFF(DAY, @dueDate, GETDATE())
        SET @fee = @daysOverdue * 0.5

        INSERT INTO MemberFees (memberId, fee) VALUES (@memberId, @fee)

        FETCH NEXT FROM overdueRentals INTO @bookId, @memberId, @rentalDate, @dueDate
    END

    CLOSE overdueRentals
    DEALLOCATE overdueRentals
END