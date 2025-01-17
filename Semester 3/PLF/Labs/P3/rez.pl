% 13. The list a1, ..., an is given and it consists of distinct integers. 
% Write a predicate to determine all subsets with aspect of "mountain" 
% (a set has a "mountain" aspect if the elements increase to a certain point and then decrease).

% mountain(L: list, F: int)
wrapper_mountain([H1, H2|T]) :-
    H1 < H2,
    mountain([H2|T], 0).

mountain([_], 1).
mountain([H1, H2|T], 0) :-
    H1 < H2,
    mountain([H2|T], 0).
mountain([H1, H2|T], _) :-
    H1 > H2,
    mountain([H2|T], 1).

% is_subset(L: list, R: list)
is_subset([], []).
is_subset([_|T], T2) :-
    is_subset(T, T2).
is_subset([H|T], [H|T2]) :-
    is_subset(T, T2).

mountain_subset(L, X) :-
    is_subset(L, X),
    wrapper_mountain(X).

process(L, Res) :-
    bagof(X, mountain_subset(L, X), Res).