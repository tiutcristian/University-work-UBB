% insertEl(E-elem, L-list, R-list) (i,i,o)
insertEl(E, [], [E]) :- !.
insertEl(E, L, [E|L]).
insertEl(E, [H|T], [H|R]) :-
    insertEl(E, T, R).

% check(L-list)
check([]).
check([_]).
check([H1, H2|T]) :-
    H1 - H2 =< 2,
    H2 - H1 =< 2,
    check([H2|T]).

% perm(L-list, R-list)
perm([], []).
perm([H|T], R) :-
    perm(T, R1),
    insertEl(H, R1, R),
    check(R).


rez(L, R) :-
    findall(RPartial, perm(L, RPartial), R).

