% Define a predicate to determine the greatest common divisor of all numbers in a list.

% gcd(X: int, Y: int, R: int)
gcd(X, 0, R) :- R is X.
gcd(X, Y, R) :- Y > 0, 
    Z is X mod Y, 
    gcd(Y, Z, R).

% gcd_list(L: list, R: int)
gcd_list([], R) :- R is 0.
gcd_list([H|T], R) :- 
    gcd_list(T, R1),
    gcd(H, R1, R).