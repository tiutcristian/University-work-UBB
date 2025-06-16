% 13.
% a. Given a linear numerical list write a predicate to remove all sequences of consecutive values.
% Eg.: remove([1, 2, 4, 6, 7, 8, 10], L) will produce L=[4, 10].

% b. For a heterogeneous list, formed from integer numbers and list of numbers; write a predicate to delete from
% every sublist all sequences of consecutive values.
% Eg.: [1, [2, 3, 5], 9, [1, 2, 4, 3, 4, 5, 7, 9], 11, [5, 8, 2], 7] =>
% [1, [5], 9, [4, 7, 9], 11, [5, 8, 2], 7]


% remove(L:list, R:list)
% remove(i, o)
remove([], []).
remove([H], [H]).
remove([H1, H2], []) :- 
    H1+1 =:= H2.
remove([H1, H2, H3 | T], R) :- 
    H1+1 =:= H2, 
    H2+1 =:= H3, 
    remove([H2, H3 | T], R).
remove([H1, H2, H3 | T], R) :- 
    H1+1 =:= H2, 
    H2+1 =\= H3, 
    remove([H3 | T], R).
remove([H1, H2 | T], [H1 | R]) :- 
    H1+1 =\= H2, 
    remove([H2 | T], R).


% remove_heterogeneous(L:list, R:list)
% remove_heterogeneous(i, o)
remove_heterogeneous([], []).
remove_heterogeneous([H|T], [H2|T2]) :-
    is_list(H), !,
    remove(H, H2),
    remove_heterogeneous(T, T2).
remove_heterogeneous([H|T], [H|T2]) :-
    remove_heterogeneous(T, T2).