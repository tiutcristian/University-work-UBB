INSERT INTO Teams (name, country) 
VALUES ('Team John', 'USA')

INSERT INTO Teams (name, country)
VALUES ('Team Michael', 'UK')

INSERT INTO Teams (name, country)
VALUES ('Team Andrei', 'Romania')

INSERT INTO Coaches (name, email, experience, team_id)
VALUES ('John Doe', 'john@doe.com', 5, 1)

INSERT INTO Coaches (name, email, experience, team_id)
VALUES ('Michael Thompson', 'm@t.com', 10, 2)

INSERT INTO Coaches (name, email, experience, team_id)
VALUES ('Andrei Popescu', 'a@p.ro', 15, 3)

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

INSERT INTO Sponsorships (sponsor_id, athlete_id, amount, start_date, end_date)
VALUES (1, 1, 1000, '2020-01-01', '2020-12-31'),
    (2, 2, 2000, '2020-01-01', '2020-12-31'),
    (1, 3, 3000, '2020-01-01', '2020-12-31')