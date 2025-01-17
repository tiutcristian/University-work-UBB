/*
Definiti un predicat ce returneaza o lista continand toate pozitiile pe care apare elem minim intr-o alta lista de nr intregi.
Ex.: [10, -14, 12, 13, -14] -> [2, 5]
*/

% det_minim(L, E)
det_minim([], 0) :- !.
det_minim([H], H) :- !.
det_minim([H|T], H) :-
    det_minim(T, R),
    H < R,
    !.
det_minim([_|T], R) :-
    det_minim(T, R).

% det_minim([10, -14, 12, 13, -14], R).


/*
det_poz(E, l1 ... ln, Crt_pos) = {
    ø, if n = 0,
    Crt_pos U det_poz(E, l2 ... ln, Crt_pos+1), if E = l1,
    det_poz(E, l2 ... ln, Crt_pos+1), otherwise
}
*/
% det_poz(E, L, R).
det_poz(_, [], _, []).
det_poz(E, [H|T], C, [C|R]) :-
    C1 is C + 1,
    det_poz(E, T, C1, R),
    E =:= H,
    !.
det_poz(E, [_|T], C, R) :-
    C1 is C + 1,
    det_poz(E, T, C1, R).

% det_poz(-14, [10, -14, 12, 13, -14], 1, R).


solve(L, R) :-
    det_minim(L, Minim),
    det_poz(Minim, L, 1, R).

% solve([10, -14, 12, 13, -14], R).