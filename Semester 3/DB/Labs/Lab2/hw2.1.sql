-- insert --------------------------------------------------
    INSERT INTO Coaches (name, email, experience) 
    VALUES ('John Doe', 'john@doe.com', 5)

    INSERT INTO Coaches (name, email, experience) 
    VALUES ('Michael Thompson', 'm@t.com', 10)

    INSERT INTO Coaches (name, email, experience)
    VALUES ('Andrei Popescu', 'a@p.ro', 1)

    INSERT INTO Teams (name, country, coach_id) 
    VALUES ('Team John', 'USA', 1)

    INSERT INTO Teams (name, country, coach_id) 
    VALUES ('Team Michael', 'UK', 2)

    INSERT INTO Teams (name, country, coach_id)
    VALUES ('Team Andrei', 'Romania', 3)

    INSERT INTO Athletes (name, email, team_id) 
    VALUES ('Alice', 'a@gmail.com', 1)
    
    INSERT INTO Athletes (name, email, team_id) 
    VALUES ('Bob', 'b@gmail.com', 1)
    
    INSERT INTO Athletes (name, email, team_id) 
    VALUES ('Charlie', 'c@gmail.com', 2)

    INSERT INTO Athletes (name, email)
    VALUES ('David', 'd@gmail.com')

    INSERT INTO Sponsors (name, country) 
    VALUES ('Nike', 'USA')
    
    INSERT INTO Sponsors (name, country) 
    VALUES ('Adidas', 'Germany')

    INSERT INTO Sponsors (name, country)
    VALUES ('Puma', 'Germany')

    --! violating integrity constraint (unique constraint)
    INSERT INTO Teams (name, country, coach_id) 
    VALUES ('Team John', 'USA', 3)

    INSERT INTO Sponsorships (sponsor_id, athlete_id, amount, start_date, end_date)
    VALUES (1, 1, 1000, '2020-01-01', '2020-12-31'),
        (2, 2, 2000, '2020-01-01', '2020-12-31'),
        (1, 3, 3000, '2020-01-01', '2020-12-31')



-- update --------------------------------------------------
    -- all athletes sponsored by Adidas will be sponsored by Puma
    UPDATE Sponsorships
    SET sponsor_id = 3
    WHERE sponsor_id = 1

    -- all teams from USA will move to Canada
    UPDATE Teams 
    SET country = 'Canada' 
    WHERE name LIKE 'Team%' AND country = 'USA'

    -- all athletes from team 1 with email starting with 'a' 
    -- will have their email changed to 'alice@gmail.com'
    UPDATE Athletes 
    SET email = 'alice@gmail.com' 
    WHERE team_id = 1 AND email LIKE 'a%'

    -- all athletes get a 10% raise except for those sponsored by Puma
    UPDATE Sponsorships
    SET amount = amount * 1.1
    WHERE sponsor_id <> 3

    -- all athletes that do not belong to a team will be assigned to team 1
    UPDATE Athletes
    SET team_id = 1
    WHERE team_id IS NULL

    -- all sponsorships with amount greater than 2000 or not sponsored by a sponsor from Germany will get a 10% raise
    UPDATE Sponsorships
    SET amount = amount * 1.1
    WHERE sponsor_id NOT IN (
        SELECT id
        FROM Sponsors
        WHERE country = 'Germany'
    ) OR amount > 2000



-- delete --------------------------------------------------
    -- delete all coaches with less than 6 years of experience
    DELETE FROM Coaches 
    WHERE experience < 6

    -- delete all sponsorships with amount between 1500 and 2500
    DELETE FROM Sponsorships 
    WHERE amount BETWEEN 1500 AND 2500

    -- delete teams that so not have a coach
    DELETE FROM Teams 
    WHERE coach_id IS NULL