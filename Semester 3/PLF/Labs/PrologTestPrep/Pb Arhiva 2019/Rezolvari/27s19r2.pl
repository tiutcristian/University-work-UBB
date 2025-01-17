% Se da o lista neliniara formata din numere si atomi.
% Sa se determine, in ordine inversa, toate elementele numerice unice din lista data.

% linearize(L, R)
linearize([], []) :- !.
linearize([H|T], R) :-
    is_list(H),
    !,
    linearize(H, R1),
    linearize(T, R2),
    append(R1, R2, R).
linearize([H|T], [H|R]) :-
    linearize(T, R).

% was_not_added(E, L)
was_not_added(_, []) :- !.
was_not_added(E, [E|_]) :-
    !, fail.
was_not_added(E, [_|T]) :-
    was_not_added(E, T).

% make_atom_set_backwards(L, R)
make_atom_set_backwards([], []) :- !.
make_atom_set_backwards([H|T], R) :-
    number(H),
    make_atom_set_backwards(T, R1),
    was_not_added(H, R1),
    !,
    append(R1, [H], R).
make_atom_set_backwards([_|T], R) :-
    make_atom_set_backwards(T, R).

% process(L, R)
process(L, R) :-
    linearize(L, L1),
    make_atom_set_backwards(L1, R).



% process([3, a, [b, [c, [4, [d, 5], b, 3]], 7]], R).
% expected: R = [7, 3, 5, 4].