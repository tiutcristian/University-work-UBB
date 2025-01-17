% Transform a list in a set, in the order of the last occurrences of elements. Eg.: [1,2,3,1,2] is transformed in [3,1,2].

% transform_list_to_set(L:list, R:resulted list)
transform_list_to_set([], []).
transform_list_to_set([H|T], Result) :- 
    transform_list_to_set(T, Result1), 
    add_element_to_set(H, Result1, Result).

% add_element_to_set(E:element, S:initial set, R:resulted set)
add_element_to_set(E, S, R) :-
    member(E, S),
    R = S.
add_element_to_set(E, S, R) :-
    \+ member(E, S),
    R = [E|S].

% member(H:head, T:tail)
member(H, [H|_]).
member(H, [_|T]) :- 
    member(H, T).