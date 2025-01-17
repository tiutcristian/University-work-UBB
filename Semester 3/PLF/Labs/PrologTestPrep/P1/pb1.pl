% det the lcm of a list of numbers

% greatest common divisor
gcd(X, 0, X) :- !.
gcd(X, Y, R) :- Y > 0, 
    Z is X mod Y, 
    gcd(Y, Z, R).

% lcm of 2 numbers
lcm(A, B, Res) :-
    gcd(A, B, D),
    Res is A * B / D.

% impl 1
lcm_list([], 1).
lcm_list([X], X) :- !.
lcm_list([H1,H2|T], Res) :-
    lcm(H1, H2, X),
    lcm_list([X|T], Res).

% impl 2
lcm_list_c([], C, C).
lcm_list_c([H|T], C, Res) :-
    lcm(H, C, C2),
    lcm_list_c(T, C2, Res).

lcm_list_c_wrapper(L, Res) :-
    lcm_list_c(L, 1, Res).


% ======================================================

% b)
insert_val(V, L, Res) :-
    insert_val_c(V, L, 1, 1, Res).

% insert_val_c(V, L, Pos, Next, Res) :- 
insert_val_c(_, [], _, _, []).
insert_val_c(V, [H|T], Pos, Pos, [H,V|Res]) :-
    !, 
    Pos1 is Pos + 1,
    Next1 is 2 * Pos,
    insert_val_c(V, T, Pos1, Next1, Res).
insert_val_c(V, [H|T], Pos, Next, [H|Res]) :-
    Pos1 is Pos + 1,
    insert_val_c(V, T, Pos1, Next, Res).