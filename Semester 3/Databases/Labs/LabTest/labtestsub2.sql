CREATE DATABASE tennis;

USE tennis;

-- Tournaments (multiple courts, multiple matches)
    -- tournament_id
    -- name
    -- start_date
    -- end_date
CREATE TABLE Tournaments(
    tournament_id INT PRIMARY KEY,
    name VARCHAR(255),
    start_date DATE,
    end_date DATE
);

-- Players
    -- player_id
    -- name
    -- prize_money
    -- no_of_points_beginning
CREATE TABLE Players(
    player_id INT PRIMARY KEY,
    name VARCHAR(255),
    prize_money INT,
    no_of_points_beginning INT
);

-- Courts (multiple tournaments)
    -- court_id
    -- name
    -- capacity
CREATE TABLE Courts(
    court_id INT PRIMARY KEY,
    name VARCHAR(255),
    capacity INT
);

-- Matches
    -- match_id
    -- player1_id
    -- player2_id
    -- court_id
    -- tournament_id
    -- date
    -- time
    -- no_of_points_player1
    -- no_of_points_player2
    -- prize_money_player1
    -- prize_money_player2
DROP TABLE IF EXISTS Matches;
CREATE TABLE Matches(
    match_id INT PRIMARY KEY,
    player1_id INT FOREIGN KEY REFERENCES Players(player_id),
    player2_id INT FOREIGN KEY REFERENCES Players(player_id),
    court_id INT FOREIGN KEY REFERENCES Courts(court_id),
    tournament_id INT FOREIGN KEY REFERENCES Tournaments(tournament_id),
    date DATE,
    time TIME,
    no_of_points_player1 INT,
    no_of_points_player2 INT,
    prize_money_player1 INT,
    prize_money_player2 INT
);

-- Court_Tournament
    -- court_id
    -- tournament_id
DROP TABLE IF EXISTS Court_Tournament;
CREATE TABLE Court_Tournament(
    court_id INT FOREIGN KEY REFERENCES Courts(court_id),
    tournament_id INT FOREIGN KEY REFERENCES Tournaments(tournament_id),
    PRIMARY KEY(court_id, tournament_id)
);



GO
CREATE OR ALTER PROCEDURE add_court_to_tournament
    @court_id INT,
    @tournament_id INT
AS
    IF EXISTS(
        SELECT * FROM Court_Tournament
        WHERE court_id = @court_id AND tournament_id = @tournament_id
    ) BEGIN
        PRINT 'Court already added to tournament';
        RETURN;
    END
    
    INSERT INTO Court_Tournament(court_id, tournament_id)
    VALUES(@court_id, @tournament_id);
GO
EXEC add_court_to_tournament 1, 1;
SELECT * FROM Court_Tournament;
EXEC add_court_to_tournament 2, 1;



GO
CREATE OR ALTER FUNCTION tournaments_with_min_C_courts(
    @C INT
) RETURNS TABLE AS
    RETURN(
        SELECT T.name
        FROM Tournaments T
        WHERE @C <= (
            SELECT COUNT(*)
            FROM Court_Tournament CT
            WHERE CT.tournament_id = T.tournament_id
        )
    );
GO
SELECT * FROM tournaments_with_min_C_courts(0);



-- players for which 
    -- there does not exist a court 
        -- where they have not played
GO
CREATE OR ALTER VIEW played_all_courts AS
    SELECT P.name
    FROM Players P
    WHERE NOT EXISTS(
        SELECT * FROM Courts C
        WHERE NOT EXISTS(
            SELECT * FROM Matches M
            WHERE 
                M.court_id = C.court_id 
                AND 
                (M.player1_id = P.player_id OR M.player2_id = P.player_id)
        )
    );
GO
SELECT * FROM played_all_courts;



-- testing stuff
INSERT INTO Tournaments(tournament_id, name, start_date, end_date)
VALUES
    (1, 'Wimbledon', '2025-01-01', '2025-01-02'),
    (2, 'US Open', '2025-01-02', '2025-01-03');
SELECT * FROM Tournaments;


INSERT INTO Players(player_id, name, prize_money, no_of_points_beginning)
VALUES
    (1, 'Federer', 1000, 100),
    (2, 'Nadal', 2000, 200),
    (3, 'Djokovic', 3000, 300);
SELECT * FROM Players;


INSERT INTO Courts(court_id, name, capacity)
VALUES
    (1, 'Court 1', 100),
    (2, 'Court 2', 200);
SELECT * FROM Courts;


INSERT INTO Matches(match_id, player1_id, player2_id, court_id, tournament_id, date, time, no_of_points_player1, no_of_points_player2, prize_money_player1, prize_money_player2)
VALUES
    (1, 1, 2, 1, 1, '2025-01-01', '12:00', 10, 5, 100, 50),
    (2, 2, 3, 2, 2, '2025-01-02', '12:00', 10, 5, 100, 50);
SELECT * FROM Matches;





SELECT * FROM Tournaments;
SELECT * FROM Players;
SELECT * FROM Courts;
SELECT * FROM Matches;
SELECT * FROM Court_Tournament;


DELETE FROM Matches where match_id = 2