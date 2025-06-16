-- a. 2 queries with the union operation; use UNION [ALL] and OR;
    -- Select all athletes that are sponsored by Adidas or Nike
    -- 1. With UNION
    SELECT id, name
    FROM Athletes
    WHERE id in (
        SELECT athlete_id
        FROM Sponsorships
        WHERE sponsor_id in (
            SELECT id
            FROM Sponsors
            WHERE name = 'Adidas'

            UNION

            SELECT id
            FROM Sponsors
            WHERE name = 'Nike'
        )
    )

    -- 2. With OR
    SELECT id, name
    FROM Athletes
    WHERE id in (
        SELECT athlete_id
        FROM Sponsorships
        WHERE sponsor_id in (
            SELECT id
            FROM Sponsors
            WHERE name = 'Adidas' OR name = 'Nike'
        ) 
    )



-- b. 2 queries with the intersection operation; use INTERSECT and IN;
    -- Select IDs of athletes that are sponsored by both Adidas and Nike
    -- 1. With INTERSECT
    SELECT athlete_id
    FROM Sponsorships
    WHERE sponsor_id = (
        SELECT id
        FROM Sponsors
        WHERE name = 'Adidas'
    )

    INTERSECT

    SELECT athlete_id
    FROM Sponsorships
    WHERE sponsor_id = (
        SELECT id
        FROM Sponsors
        WHERE name = 'Nike'
    )

    -- 2. With IN
    SELECT athlete_id
    FROM Sponsorships
    WHERE sponsor_id = (
        SELECT id
        FROM Sponsors
        WHERE name = 'Adidas'
    ) AND athlete_id IN (
        SELECT athlete_id
        FROM Sponsorships
        WHERE sponsor_id = (
            SELECT id
            FROM Sponsors
            WHERE name = 'Nike'
        )
    )



-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;
    -- Select IDs of athletes that are sponsored by Adidas but not by Nike
    -- 1. With EXCEPT
    SELECT athlete_id
    FROM Sponsorships
    WHERE sponsor_id = (
        SELECT id
        FROM Sponsors
        WHERE name = 'Adidas'
    )

    EXCEPT

    SELECT athlete_id
    FROM Sponsorships
    WHERE sponsor_id = (
        SELECT id
        FROM Sponsors
        WHERE name = 'Nike'
    )

    -- 2. With NOT IN
    SELECT athlete_id
    FROM Sponsorships
    WHERE sponsor_id = (
        SELECT id
        FROM Sponsors
        WHERE name = 'Adidas'
    ) AND athlete_id NOT IN (
        SELECT athlete_id
        FROM Sponsorships
        WHERE sponsor_id = (
            SELECT id
            FROM Sponsors
            WHERE name = 'Nike'
        )
    )



-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); 
-- one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- INNER JOIN + many-to-many (Sponsorships, RaceResults)
-- Find the athletes (id+name) sponsored by Nike that participated in race with id 1
SELECT A.id, A.name
FROM Athletes A
JOIN Sponsorships SS ON A.id = SS.athlete_id
JOIN Sponsors S ON SS.sponsor_id = S.id
JOIN RaceResults RR ON A.id = RR.athlete_id
WHERE S.name = 'Nike' AND RR.race_id = 1;

-- LEFT JOIN + 3 tables
-- Find all athletes (id+name) and their total time (both in seconds and minutes) that are sponsored by Nike
SELECT A.id, A.name, RR.total_time, RR.total_time/60 AS total_time_minutes
FROM Athletes A
LEFT JOIN Sponsorships SS ON A.id = SS.athlete_id
LEFT JOIN Sponsors S ON SS.sponsor_id = S.id
LEFT JOIN RaceResults RR ON A.id = RR.athlete_id
WHERE S.name = 'Nike';

-- RIGHT JOIN
-- Find all coaches and their teams if they have one
SELECT C.name AS coach_name, T.name AS team_name
FROM Coaches C
RIGHT JOIN Teams T ON T.coach_id = C.id;

-- FULL JOIN
-- Find all coaches and all teams
SELECT C.name AS coach_name, T.name AS team_name
FROM Coaches C
FULL JOIN Teams T ON T.coach_id = C.id;



-- e. 2 queries with the IN operator and a subquery in the WHERE clause;
-- in at least one case, the subquery must include a subquery in its own WHERE clause;

-- Find all athletes that are sponsored by Nike
SELECT A.name
FROM Athletes A
WHERE A.id IN (
    SELECT SS.athlete_id
    FROM Sponsorships SS
    WHERE SS.sponsor_id IN (
        SELECT S.id
        FROM Sponsors S
        WHERE S.name LIKE 'Nike%'
    )
)

-- Find all teams with athletes that are sponsored by Nike
SELECT DISTINCT T.id, T.name
FROM Teams T
JOIN Athletes A ON T.id = A.team_id
WHERE A.id IN (
    SELECT SS.athlete_id
    FROM Sponsorships SS
    WHERE SS.sponsor_id IN (
        SELECT S.id
        FROM Sponsors S
        WHERE S.name LIKE 'Nike%'
    )
)



-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;

-- Find all teams with athletes that are sponsored by Nike
SELECT T.id, T.name
FROM Teams T
WHERE EXISTS (
    SELECT A.id
    FROM Athletes A
    WHERE (A.team_id = T.id) AND A.id IN (
        SELECT SS.athlete_id
        FROM Sponsorships SS
        WHERE SS.sponsor_id IN (
            SELECT S.id
            FROM Sponsors S
            WHERE S.name LIKE 'Nike%'
        )
    )
)

-- Find all races that have finished (have results)
SELECT R.name
FROM Races R
WHERE EXISTS (
    SELECT RR.race_id
    FROM RaceResults RR
    WHERE RR.race_id = R.id
)



-- g. 2 queries with a subquery in the FROM clause; 

-- Find all teams that have at least 1 athlete sponsored by Nike AND at least 1 athlete sponsored by Adidas
SELECT T.id, T.name
FROM (
    (
        SELECT DISTINCT A.team_id
        FROM Athletes A
        JOIN Sponsorships SS ON A.id = SS.athlete_id
        JOIN Sponsors S ON SS.sponsor_id = S.id
        WHERE S.name = 'Nike'
    )
    INTERSECT
    (
        SELECT DISTINCT A.team_id
        FROM Athletes A
        JOIN Sponsorships SS ON A.id = SS.athlete_id
        JOIN Sponsors S ON SS.sponsor_id = S.id
        WHERE S.name = 'Adidas'
    )
) AS TID
JOIN Teams T ON T.id = TID.team_id

-- Find top 3 athletes that have a name starting with 'A' and an email starting with 'a' ordered by email in descending order
SELECT TOP 3 *
FROM (
    SELECT *
    FROM Athletes A
    WHERE A.name LIKE 'A%'
) as Ath
WHERE Ath.email LIKE 'a%'
ORDER BY Ath.email DESC



-- h. 4 queries with the GROUP BY clause
-- 3 of which also contain the HAVING clause; 
-- 2 of the latter will also have a subquery in the HAVING clause
-- use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

-- Count how many athletes are in each team
SELECT T.name, COUNT(A.id) AS athletes_count
FROM Teams T
LEFT JOIN Athletes A ON T.id = A.team_id
GROUP BY T.name

-- Find the teams with at least 2 athletes
SELECT T.name, COUNT(A.id) AS athletes_count
FROM Teams T
LEFT JOIN Athletes A ON T.id = A.team_id
GROUP BY T.name
HAVING COUNT(A.id) >= 2

-- Find the teams that have more athletes than 'Team 2' and if there are more than 3, show only the top 3 by the number of athletes
SELECT TOP 3 
T.name, COUNT(A.id) AS athletes_count
FROM Teams T
LEFT JOIN Athletes A ON T.id = A.team_id
GROUP BY T.name
HAVING COUNT(A.id) > (
    SELECT COUNT(A.id)
    FROM Teams T
    LEFT JOIN Athletes A ON T.id = A.team_id
    WHERE T.name = 'Team 2'
)
ORDER BY athletes_count DESC

--! Execute this before running the next query
UPDATE Athletes SET team_id = 5 WHERE team_id IS NULL;

-- Find the teams with the most athletes and the number of members including the coach
SELECT T.name, COUNT(A.id) AS athletes_count, COUNT(A.id) + 1 AS total_members
FROM Teams T
LEFT JOIN Athletes A ON T.id = A.team_id
GROUP BY T.name
HAVING COUNT(A.id) = (
    SELECT MAX(athletes_count)
    FROM (
        SELECT COUNT(A.id) AS athletes_count
        FROM Teams T
        LEFT JOIN Athletes A ON T.id = A.team_id
        GROUP BY T.name
    ) AS T
)
ORDER BY total_members DESC



-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); 
-- rewrite 2 of them with aggregation operators
-- and the other 2 with IN / [NOT] IN.

-- Find the maximum amount sponsored by a sponsor from Germany and the amount in euros (in db is stored in dollars)
SELECT MAX(SS.amount) * 0.85 AS max_amount_euro
FROM Sponsorships SS
WHERE SS.sponsor_id = ANY (
    SELECT S.id
    FROM Sponsors S
    WHERE S.country = 'Germany'
)

-- rewritten with IN:
SELECT MAX(SS.amount) AS max_amount
FROM Sponsorships SS
WHERE SS.sponsor_id IN (
    SELECT S.id
    FROM Sponsors S
    WHERE S.country = 'Germany'
)

-- Select all sponsors that have contributed with the maximum amount
SELECT S.name
FROM Sponsors S
JOIN Sponsorships SS ON S.id = SS.sponsor_id
WHERE SS.amount >= ALL (
    SELECT SS.amount
    FROM Sponsorships SS
)

-- rewritten with MAX:
SELECT S.name
FROM Sponsors S
JOIN Sponsorships SS ON S.id = SS.sponsor_id
WHERE SS.amount = (
    SELECT MAX(SS.amount)
    FROM Sponsorships SS
)

-- Find all athletes that are not sponsored by Nike
SELECT A.name
FROM Athletes A
WHERE A.id <> ALL (
    SELECT SS.athlete_id
    FROM Sponsorships SS
    WHERE SS.sponsor_id = (
        SELECT S.id
        FROM Sponsors S
        WHERE S.name = 'Nike'
    )
)

-- rewritten with NOT IN:
SELECT A.name
FROM Athletes A
WHERE A.id NOT IN (
    SELECT SS.athlete_id
    FROM Sponsorships SS
    WHERE SS.sponsor_id = (
        SELECT S.id
        FROM Sponsors S
        WHERE S.name = 'Nike'
    )
)

-- Find all sponosors that have sponsored more than the minimum amount (at least once)
SELECT DISTINCT S.name
FROM Sponsors S
JOIN Sponsorships SS ON S.id = SS.sponsor_id
WHERE SS.amount > ANY (
    SELECT SS.amount
    FROM Sponsorships SS
)

-- rewritten with MIN:
SELECT DISTINCT S.name
FROM Sponsors S
JOIN Sponsorships SS ON S.id = SS.sponsor_id
WHERE SS.amount > (
    SELECT MIN(SS.amount)
    FROM Sponsorships SS
)



/***************************************************************************************************/
-- You must use:
    -- arithmetic expressions in the SELECT clause in at least 3 queries;
    -- conditions with AND, OR, NOT, and parentheses in the WHERE clause in at least 3 queries;
    -- DISTINCT in at least 3 queries, ORDER BY in at least 2 queries, and TOP in at least 2 queries.
/***************************************************************************************************/