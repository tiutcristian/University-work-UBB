/*
Definiti un predicat care creeaza dintr-o lista de numere o lista de frecvente de aparitii ale unui numar, definite ca perechi [nr, frecventa].
Ex.: [11, 22, 11, 22, 11, 33, 11] -> [[11, 4], [22, 2], [33, 1]]
*/

% det_frecv(E, L, R)
det_frecv(_, [], 0).
det_frecv(E, [H|T], R) :-
    det_frecv(E, T, R1),
    H =:= E,
    !,
    R is R1 + 1.
det_frecv(E, [_|T], R) :-
    det_frecv(E, T, R).


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


% det_frecv_list([_|T], [], []).
% det_frecv_list([H|T], L, [L1|R2]) :-
%     det_frecv(H, L, R1),
%     L1 is [H, R1].


det_frecv_list([], _, []).
det_frecv_list([H|T], L, [[H, R1]|R2]) :-
    det_frecv(H, L, R1),
    det_frecv_list(T, L, R2).



% increase(E, L, R).



/*
    solve((l1 ... ln), ((e1,f1),...,(en,fn))) = {
        l1 is in (e1, ... , en)
    }
*/