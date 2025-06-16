# Seminar 1

## Problem 1
### Write a function that removes all unique elements from a list.
Remove all elements that appear only once in the list.
```
remove([A1, ..., An], [B1, ..., Bn]) = {
    • [] if n = 0,
    • A1 U remove([A2, ..., An], [B1, ..., Bn]) 
            if countOcc(A1, [B1, ..., Bn]) > 1,
    • remove([A2, ..., An], [B1, ..., Bn]) otherwise
}
```
\
Count the number of occurrences of an element in a list.
```
countOcc(x, [A1, ..., An]) = {
    • 0 if n = 0,
    • 1 + countOcc(x, [A2, ..., An]) if x = A1,
    • countOcc(x, [A2, ..., An]) otherwise
}
```
\
Add an element to the end of a list.
```
add_to_end(x, [A1, ..., An]) = {
    • [x] if n = 0,
    • [A1, ..., An, x] otherwise
}
```

## Problem 2
### Remove all ascending subsequences from a list.
```
f([L1, ..., Ln]) = {
    • [] if n = 0,
    • f([L1]) if n = 1,
    • f([]) if n = 2 and L1 < L2,
    • f([L2, ..., Ln]) if L1 < L2 < L3,
    • f([L3, ..., Ln]) if L1 < L2 and L2 >= L3,
    • [L1] U f([L2, ..., Ln]) otherwise
}
```