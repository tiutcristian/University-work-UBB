/*
Se dau doua liste A si B.
a) Sa se determine valorile elementelor maxime din cele doua liste.
b) Sa se creeze o lista noua N care va contine valorile maxime obtinute dublate

Ex.:
A = [4, 7, 2, 6]
B = [11, 10, 9]
a)  Max_a = 7
    Max_b = 11
b)  NL = [ 14, 22 ]
*/

el_max([], 0) :- !.
el_max([H], H) :- !.
el_max([H|T], H) :-
    el_max(T, R),
    H > R, !.
el_max([_|T], R) :-
    el_max(T, R).

solve_a(A, B, Max_a, Max_b) :-
    el_max(A, Max_a),
    el_max(B, Max_b).

solve_b(Max_a, Max_b, [Dbl_a, Dbl_b]) :-
    Dbl_a is 2 * Max_a,
    Dbl_b is 2 * Max_b.

% solve_a([4, 7, 2, 6], [11, 10, 9], Max_a, Max_b), solve_b(Max_a, Max_b, R).