% is_list()
% atomic()
% number()

% Given a heterogeneous list composed of numbers, symbols, and lists of numbers
% remove the sublists

process([], []).
process([H|T], R) :- 
    is_list(H), 
    process(T, R).
process([H|T], [H|R]) :-
    atomic(H),
    process(T, R).

% Test cases
% process([1, 2, [3, 4], 5, [6, 7], 8], R).