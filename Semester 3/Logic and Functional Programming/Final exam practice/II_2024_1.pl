% generare_aux(L: list, N_Y: integer, N: integer)
generare_aux([], _, 0) :- !.
generare_aux(['R'|L], 0, N) :- !,
    N1 is N - 1,
    generare_aux(L, 0, N1).
generare_aux(['R'|L], N_Y, N) :-
    N1 is N - 1,
    generare_aux(L, N_Y, N1).
generare_aux(['Y'|L], N_Y, N) :-
    N1 is N - 1,
    N_Y1 is N_Y - 1,
    generare_aux(L, N_Y1, N1).

generare(L) :-
    generare_aux(L, 3, 5).