% Write a predicate that transforms a heterogeneous list into a simple list
transform([], []).
transform([H|T], [H|R]) :- 
    number(H), 
    !, 
    transform(T, R).

transform([H|T], R) :-
    is_list(H),
    !,
    transform(H, RH),
    transform(T, RT),
    append(RH, RT, R).