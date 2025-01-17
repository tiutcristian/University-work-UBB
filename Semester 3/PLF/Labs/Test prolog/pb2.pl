/*
Definiti un predicat ce intercaleaza 2 liste sortate de nr intregi si elimina valorile duplicate.
Ex.: L1 = [1,2,3,5,7], L2 = [2,4,6,8] -> R = [1,2,3,4,5,6,7,8]
*/

% elim_duplicate(L, R)
elim_duplicate([], []).
elim_duplicate([H|T], [H|R1]) :-
    elim_duplicate(T, R1),
    nu_apartine(H, R1),
    !.
elim_duplicate([_|T], R1) :-
    elim_duplicate(T, R1).


nu_apartine(_, []) :- !.
nu_apartine(E, [H|T]) :-
    nu_apartine(E, T),
    E =\= H.


% interclasare(l11 ... l1n, l21 ... l2m) = {
%     ø, if n = 0 and m = 0
%     l11, if m = 0
%     l21, if n = 0
%     l11 U interclasare(l12 ... l1n, l21 ... l2m), if l11 < l21
%     l21 U interclasare(l11 ... l1n, l22 ... l2m), otherwise
% }
interclasare([], [], []).
interclasare([H|T], [], [H|R]) :-
    interclasare(T, [], R).
interclasare([], [H|T], [H|R]) :-
    interclasare([], T, R).
interclasare([H1|T1], [H2|T2], [H1|R]) :-
    interclasare(T1, [H2|T2], R),
    H1 < H2,
    !.
interclasare([H1|T1], [H2|T2], [H2|R]) :-
    interclasare([H1|T1], T2, R).


solve(L1, L2, R) :-
    interclasare(L1, L2, R1),
    elim_duplicate(R1, R).

% solve([1,2,3,4,5], [6,7,8], R).