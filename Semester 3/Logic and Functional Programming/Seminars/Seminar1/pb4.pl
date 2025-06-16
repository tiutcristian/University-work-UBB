% Return true if a list has an even number of elements and false otherwise.

%Impl 1:
isEven([]).
isEven([_|T]) :- not(isEven(T)).

%Impl 2:
isEven2([]).
isEven2([_,_|T]) :- isEven2(T).