% suma(L-list, S-number)
% flow model: (i,o)
suma([],[]).
suma([H|T], S) :- 
    suma(T, TS), 
    S is H + TS.

% process(L-list, R-list)
% flow model: (i,o)
process([],[]).
process([H|T], [H1|R]) :- 
    is_list(H),
    suma(H, Sum), 
    Sum mod 2 =:= 1,
    !,
    H = [H1|_],
    process(T, R).
process([H|T], [H|R]) :-
    process(T, R).