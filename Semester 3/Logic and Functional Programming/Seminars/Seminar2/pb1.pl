% function that removes all unique elements from a list

% remove_unique(List, List, Result)
remove_unique([], _, []).
remove_unique([H|T], L, [H|R]) :- 
    countOcc(H, L, Count),
    Count > 1,
    remove_unique(T, L, R).
remove_unique([H|T], L, R) :-
    countOcc(H, L, Count),
    Count =:= 1,
    remove_unique(T, L, R).


% remove_unique_col(List, List, Coll, Result)
remove_unique_col([], _, C, C).
remove_unique_col([H|T], L, Col, R) :- 
    countOccCol(H, L, 0, Count),
    Count > 1,
    Col1 = [H|Col],
    remove_unique_col(T, L, Col1, R).
remove_unique_col([H|T], L, Col, R) :-
    countOccCol(H, L, 0, Count),
    Count =:= 1,
    remove_unique_col(T, L, Col, R).
remove_unique_col(L,R) :- remove_unique_col(L, L, [], R).



% countOcc(Elem, List, Result)
% (i, i, o), (i, i, i)
countOcc(_, [], 0).
countOcc(E, [H|T], Count) :- 
    H =:= E,
    Count is Count1 + 1,
    countOcc(E, T, Count1).
countOcc(E, [H|T], Count) :-
    H =\= E,
    countOcc(E, T, Count).



countOcc2(_, [], 0).
countOcc2(E, [E|T], Count) :- 
    Count is Count1 + 1,
    countOcc(E, T, Count1).
countOcc2(E, [H|T], Count) :-
    H =\= E,
    countOcc(E, T, Count).



% countOccCol(Elem, List, Coll, Result)
% (i, i, i, o)
countOccCol(_, [], C, C).
countOccCol(E, [E|T], Col, R) :- 
    Col1 is Col + 1,
    countOccCol(E, T, Col1, R).
countOccCol(E, [H|T], Col, R) :-
    H =\= E,
    countOccCol(E, T, Col, R).