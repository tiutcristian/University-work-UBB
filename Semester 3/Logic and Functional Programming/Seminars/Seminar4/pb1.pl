insertEl(E, L, [E|L]).
insertEl(E, [H|T], [H|R]) :-
    insertEl(E, T, R).

arr([H|_], 1, [H]).
arr([_|T], K, R) :-
    K >= 1,
    arr(T, K, R).
arr([H|T], K, R) :-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).

suma([], 0).
suma([H|T], S) :- 
    suma(T, S1), 
    S is S1 + H.

prod([], 1).
prod([H|T], P) :- 
    prod(T, P1), 
    P is P1 * H.

onesol(L, K, S, P, A) :- 
    arr(L, K, A), 
    suma(A, S), 
    prod(A, P).

mainAllSol(L, K, S, P, R) :-
    findall(A, onesol(L, K, S, P, A), R).