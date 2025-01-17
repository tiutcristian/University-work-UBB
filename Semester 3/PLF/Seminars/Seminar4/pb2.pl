% valley(l1l2...ln, F) = {
%     True, if n = 1, F = 1
%     valley(l2...ln, 0), if l1 > l2 and F = 0
%     valley(l2...ln, 1), if l1 < l2 and F = 1
%     False, otherwise
% }
valley([_], 1).
valley([H1, H2|T], 0) :- 
    H1 > H2, 
    valley([H2|T], 0).
valley([H1, H2|T], 1) :-
    H1 < H2,
    valley([H2|T], 1).


% main_valley(l1l2...ln) = {
%     valley(l1l2...ln, 0), if l1 > l2
%     false, otherwise
% }
main_valley([H1, H2|T]) :-
    H1 > H2,
    valley([H1, H2|T], 0).


% oneSol(l1l2...ln) = p1p2...pn, if 
%         p1p2...pm = perm(subset(l1l2...ln))
%         and valley(p1p2...pm)
oneSol(L, P) :-
    subset(L, S),
    perm(S, P),
    main_valley(P).


% mainAllSol(l1l2...ln) = findAll(oneSol(l1l2...ln))
mainAllSol(L, R) :-
    findall(RPartial, oneSol(L, RPartial), R).


% ==================== UTILS ====================
% subset(L-list, R-list)
subset([], []).
subset([H|T], [H|R]) :- 
    subset(T, R).
subset([_|T], R) :-
    subset(T, R).

% insertEl(E-elem, L-list, R-list) (i,i,o)
insertEl(E, L, [E|L]).
insertEl(E, [H|T], [H|R]) :-
    insertEl(E, T, R).

% perm(L-list, R-list)
perm([], []).
perm([H|T], R) :-
    perm(T, R1),
    insertEl(H, R1, R).