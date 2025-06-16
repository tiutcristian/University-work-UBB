/*
Se da o lista L de numere si de atomi.
a) Sa se stearga toti atomi si toate elementele de valoare impara din lista si sa se determine cmmdc al acestei liste.
b) Sa se dubleze elementele ramase in lista.

Ex.:
L = [ a, m, 10, 5, 6, 2, 3, 12, 2, n, z ]
a) NL = [10, 6, 2, 12, 2]
b) NL = [10, 10, 6, 6, 2, 2, 12, 12, 2, 2]
*/

% a)
del_atom_odd([], []).
del_atom_odd([H|T], [H|R]) :-
    number(H),
    H2 is H mod 2,
    H2 =:= 0,
    !,
    del_atom_odd(T, R).
del_atom_odd([_|T], R) :-
    del_atom_odd(T, R).

gcd(X, 0, X) :- !.
gcd(X, Y, R) :- 
    Y > 0, 
    Z is X mod Y, 
    gcd(Y, Z, R).

gcd_list([], 0) :- !.
gcd_list([H|T], R) :- 
    gcd_list(T, R1),
    gcd(H, R1, R).

process_a(L, R, G) :-
    del_atom_odd(L, R),
    gcd_list(R, G).

% b)
dbl_el([], []) :- !.
dbl_el([H|T], [H,H|R]) :-
    dbl_el(T,R).

process_b(L, R) :-
    dbl_el(L, R).
    
% process_a([ a, m, 10, 5, 6, 2, 3, 12, 2, n, z ], Ra, G), process_b(Ra, Rb), write(Rb).