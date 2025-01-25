----------------- Setup for second part of the homework -----------------

-- Insert a bit more sponsorships
INSERT INTO Sponsorships (sponsor_id, athlete_id, amount, start_date, end_date)
VALUES  (1, 1, 1000, '2020-01-01', '2020-12-31'),
        (1, 2, 2000, '2020-01-01', '2020-12-31'),
        (2, 2, 6000, '2020-01-01', '2020-12-31'),
        (2, 3, 7000, '2020-01-01', '2020-12-31');
-- Nike sponsors 1 and 2
-- Adidas sponsors 2 and 3
-- Puma sponsors 1 and 3 (previously inserted)

-- Insert a new event
INSERT INTO Events (name, [location]) VALUES ('Event 1', 'Location 1');

-- Insert a new swim pool
INSERT INTO SwimPools (name, [location], [length], [width], [depth]) VALUES ('Pool 1', 'Location 1', 50, 25, 3);

-- Insert a new bike track
INSERT INTO BikeTracks (name, [location], [length], [difficulty]) VALUES ('Bike Track 1', 'Location 1', 100, 1);

-- Insert a new running track
INSERT INTO RunTracks (name, [location], [length], [difficulty]) VALUES ('Running Track 1', 'Location 1', 100, 1);

-- Insert a new race
INSERT INTO Races (name, [date], swim_pool_id, bike_track_id, run_track_id, event_id)
VALUES ('race1', '2020-01-01', 1, 1, 1, 1);

-- Insert a new RaceResult
INSERT INTO RaceResults (athlete_id, race_id, place_occupied, total_time, swim_time, bike_time, run_time)
VALUES (1, 1, 1, 4000, 1000, 2000, 1000);

-- Insert a new team withouth a coach
INSERT into Teams (name, country) VALUES ('Team 2', 'Alaska');

-- Insert a new coach
INSERT into Coaches (name, email, experience) VALUES ('Coach 2', 'c2@gmail.com', 2);

-- Put Alice into a team
UPDATE Athletes SET team_id = 2 WHERE name = 'Alice';