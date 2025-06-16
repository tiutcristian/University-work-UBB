% subset(L-list, R-list)
subset([], []).
subset([H|T], [H|R]) :- 
    subset(T, R).
subset([_|T], R) :-
    subset(T, R).



% combinations(L-list, K-number, R-list)
comb([H|_], 1, [H]) :- !.
comb([_|T], K, R) :-
    K >= 1,
    comb(T, K, R).
comb([H|T], K, [H|R]) :-
    K > 1,
    K1 is K - 1,
    comb(T, K1, R).



% insertEl(E-elem, L-list, R-list) (i,i,o)
insertEl(E, [], [E]) :- !.
insertEl(E, L, [E|L]).
insertEl(E, [H|T], [H|R]) :-
    insertEl(E, T, R).

% perm(L-list, R-list)
perm([], []).
perm([H|T], R) :-
    perm(T, R1),
    insertEl(H, R1, R).



% arr(L-list, K-number, R-list) (i,i,o)
arr([H|_], 1, [H]).
arr([_|T], K, R) :-
    K >= 1,
    arr(T, K, R).
arr([H|T], K, R) :-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).