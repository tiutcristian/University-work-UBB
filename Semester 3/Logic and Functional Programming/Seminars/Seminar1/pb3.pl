% Keep the prime numbers from a list

% filterPrime(List, Result)
% filterPrime(i, o)

filterPrime([], []).
% filterPrime([], Res) :- Res = [].
filterPrime([X|Y], Res) :- 
    isPrime(X),
    filterPrime(Y, Res1),
    Res = [X|Res1].
filterPrime([H|T], Res) :-
    not(isPrime(H)),
    filterPrime(T, Res).

isPrime(X) :- X > 1, isPrime(X, 2). % wrapper function
% isPrime(X, D)
isPrime(X, D) :- D >= X.
isPrime(X, D) :- D < X,
    X mod D =\= 0, D1 is D + 1,
    isPrime(X, D1).