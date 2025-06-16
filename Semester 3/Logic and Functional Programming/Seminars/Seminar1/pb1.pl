% Write a function that checks if a number contains only the digits 4 and 7.

f(4).
f(7).
f(X) :- X1 is X mod 10,
    X1 =:= 4,
    X2 is X div 10,
    f(X2).
f(X) :- X1 is X mod 10,
    X1 =:= 7,
    X2 is X div 10,
    f(X2).

