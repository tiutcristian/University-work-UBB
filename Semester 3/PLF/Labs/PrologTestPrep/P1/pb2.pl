% sort(L, SL)
mergesort([], []).
mergesort([X],[X]) :- !.
mergesort(L, Res) :-
    split(L, L1, L2),
    mergesort(L1, SL1),
    mergesort(L2, SL2),
    merge(SL1, SL2, Res).

split([], [], []).
split([X], [X], []).
split([H1,H2|T], [H1|L1], [H2|L2]) :-
    split(T, L1, L2).

merge([], [], []) :- !.
merge([], L, L).
merge(L, [], L).
merge([H1|T1], [H2|T2], [H1|Res]) :-
    H1 < H2, !,
    merge(T1, [H2|T2], Res).
merge([H1|T1], [H2|T2], [H2|Res]) :-
    merge([H1|T1], T2, Res).