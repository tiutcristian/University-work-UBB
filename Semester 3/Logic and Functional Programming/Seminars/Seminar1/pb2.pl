% Compute sum of numbers to N

g(0, Res) :- Res is 0.
g(X, Res) :- X > 0,
    X1 is X - 1,
    g(X1, Res1),
    Res is Res1 + X.