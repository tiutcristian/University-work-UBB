% data fiind o lista de nr intregi, adaugati o val data dupa primul, al treilea, al 7 lea, al 15 lea ... element al listei
% pentru prima adaugare elem trebuie adaugat o data, pentru a doua de 2 ori, pentru a treia de 3 ori si asa mai departe
% Ex: [1,2,3,4,5,6,7,8,9,10], 0 => [1,0,2,3,0,0,4,5,7,0,0,0,8,9,10]


is_power_of_2(1) :- !.
is_power_of_2(N) :- 
    N mod 2 =:= 0,
    N1 is N // 2,
    is_power_of_2(N1).

append_n_times(L, _, 0, L) :- !.
append_n_times(L, E, N, [E|R]) :-
    N > 0, 
    N1 is N - 1,
    append_n_times(L, E, N1, R).

add_elem([], _, _, []) :- !.
add_elem([H|T], E, CrtPos, [H|R]) :-
    CrtPos1 is CrtPos + 1,
    \+ is_power_of_2(CrtPos1),
    !,
    add_elem(T, E, CrtPos1, R).
add_elem([H|T], E, CrtPos, [H|R1]) :-
    CrtPos1 is CrtPos + 1,
    add_elem(T, E, CrtPos1, R),
    Sqrt is round(sqrt(CrtPos)),
    append_n_times(R, E, Sqrt, R1).

add_elem_wrapper(L, E, R) :- 
    add_elem(L, E, 1, R).

% add_elem_wrapper([1,2,3,4,5,6,7,8,9,10], 0, R), write(R).


% add_elem(l1l2...ln, E, C) = {
%   Ø, if n = 0
%   l1 U add_elem(l2...ln, E, C+1), if C+1 is not a power of 2
%   [sqrt(C) times E] U add_elem(l2...ln, E, C+1), if C+1 is a power of 2
% }