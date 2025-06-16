/*
Se da o lista L de numere intregi, pozitive si negative.
a) Sa se creeze 2 liste N si P astfel: P va contine doar numerele pozitive, iar N va contine numerele negative.
b) Determinati elementele minime din cele doua liste create.
L = [2, 4, 9, -7, -6, 4, -5]
*/

% a) =======================================
% solve_a(i, o, o)
solve_a([], [], []) :- !.
solve_a([H|T], [H|N], P) :-
    H < 0,
    !,
    solve_a(T, N, P).
solve_a([H|T], N, [H|P]) :-
    solve_a(T, N, P).

% b) =======================================
% (i, i, o)
minim(A, B, A) :-
    A < B, !.
minim(_, B, B).

% (i, o)
min_elem([], 0) :- !.
min_elem([H], H) :- !.
min_elem([H|T], ResMinim) :- 
    min_elem(T, MinimPartial),
    minim(H, MinimPartial, ResMinim).

% (i, i, o, o)
solve_b(N, P, MinimN, MinimP) :-
    min_elem(N, MinimN),
    min_elem(P, MinimP).

% solve_a([2, 4, 9, -7, -6, 4, -5], N, P), solve_b(N, P, MinimN, MinimP).