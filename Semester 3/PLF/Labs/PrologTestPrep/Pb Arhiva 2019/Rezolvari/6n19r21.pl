/*
Se da o lista L de numere si atomi.
a) Sa se stearga toate elementele de valoare para din lista.
b) Sa se dubleze elementele numerice ramase si sa se determine cel mai mic multiplu comun al elementelor numerice din aceasta lista.

ex.: 
L = [ a, m, 10, 5, 6, 2, 3, 10, n, z ]
a) Ln = [ a, m, 5, 5, 3, 3 n, z ]
b) cmmmcL = 15
*/

del_even([], []) :- !.
del_even([H|T], R) :-
    number(H),
    H mod 2 =:= 0,
    !,
    del_even(T, R).
del_even([H|T], [H|R]) :-
    del_even(T, R).


dbl_nr([], []) :- !.
dbl_nr([H|T], [H,H|R]) :-
    number(H),
    !,
    dbl_nr(T, R).
dbl_nr([H|T], [H|R]) :-
    dbl_nr(T, R).


process_list(L, R) :-
    del_even(L, R1),
    dbl_nr(R1, R).


cmmdc(X, 0, X) :- !.
cmmdc(X, Y, R) :-
    Y > 0,
    Z is X mod Y,
    cmmdc(Y, Z, R).


cmmmc(A, B, R) :-
    cmmdc(A, B, R1),
    R is A * B / R1.


cmmmc_list([], 1) :- !.
cmmmc_list([H|T], R) :-
    cmmmc_list(T, R1),
    number(H),
    !,
    cmmmc(H, R1, R).
cmmmc_list([_|T], R) :-
    cmmmc_list(T, R).


solve(L, R, C) :-
    process_list(L, R),
    cmmmc_list(R, C).

% solve([ a, m, 10, 5, 6, 2, 3, 10, n, z ], R, C).