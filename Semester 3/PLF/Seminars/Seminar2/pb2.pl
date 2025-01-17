% Remove all ascending subsequences from a list.
f([], []).
f([H], [H]).
f([H1, H2], []) :- 
    H1 < H2.
f([H1, H2, H3 | T], R) :- 
    H1 < H2, 
    H2 < H3, 
    f([H2, H3 | T], R).
f([H1, H2, H3 | T], R) :- 
    H1 < H2, 
    H2 >= H3, 
    f([H3 | T], R).
f([H1, H2 | T], [H1 | R]) :- 
    H1 >= H2, 
    f([H2 | T], R).