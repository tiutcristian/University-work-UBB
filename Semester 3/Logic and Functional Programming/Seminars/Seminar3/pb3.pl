% Given a list of numbers and sublists of numbers, 
% remove the odd numbers from the sublists that have a mountain shape

% remove_odd(L: list, R: list)
remove_odd([], []).
remove_odd([H|T], [H|R]) :- 
    H mod 2 =:= 0, !,
    remove_odd(T, R).
remove_odd([_|T], R) :-
    remove_odd(T, R).

% process(L: list, R: list)
process([], []).
process([H|T], [H1|R]) :- 
    is_list(H),
    wrapper_mountain(H), !,
    remove_odd(H, H1),
    process(T, R).
process([H|T], [H|R]) :-
    process(T, R).

% mountain(L: list, F: int)
mountain([_], 1).
mountain([H1, H2|T], 0) :-
    H1 < H2,
    mountain([H2|T], 0).
mountain([H1, H2|T], _) :-
    H1 > H2,
    mountain([H2|T], 1).

% wrapper_mountain(L: list)
wrapper_mountain([H1, H2|T]) :-
    H1 < H2,
    mountain([H2|T], 0).



% Tests
% process([1, [2, 3, 4], [5, 6, 7], [8, 9, 10], [11, 12, 13], 14], R), R = [1, [2, 4], [5, 6, 7], [8, 10], [11, 12, 13], 14].