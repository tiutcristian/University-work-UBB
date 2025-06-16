# Seminar 3
## Pb 1
#### Given a heterogeneous list composed of numbers, symbols, and lists of numbers remove the sublists
```
process(l1 l2 ... ln) = {
    Ø, if n = 0
    process(l2 ... ln), if l1 is a list
    l1 U process(l2 ... ln), if l1 is not a list
}
```

## Pb 2
#### Given a list of numbers and sublists of numbers, substitute each sublist for which the sum of elements is odd with the first element of the sublist (We assume sublists are non-empty)
```
process(l1 l2 ... ln) = {
    Ø, if n = 0
    l11 U process(l2 ... ln), if l1 is a list AND sum(l1) % 2 = 1
    l1 U process(l2 ... ln), if l1 is not a list OR sum(l1) % 2 = 0
}
```

## Pb 3
#### Given a list of numbers and sublists of numbers, remove the odd numbers from the sublists that have a mountain shape (i.e., the numbers in the sublist are increasing up to a certain point and then decreasing)
```
remove_odd(l1 l2 ... ln) = {
    Ø, if n = 0
    l1 U remove_odd(l2 ... ln), if l1 % 2 == 0
    remove_odd(l2 ... ln), otherwise
}

mountain(l1 l2 ... ln, F) = {
    true, if n = 1, F = 1
    mountain(l2 ... ln, 0), if l1 < l2 AND F = 0
    mountain(l2 ... ln, 1), if l1 > l2 AND F = 0
    mountain(l2 ... ln, 1), if l1 > l2 AND F = 1
    false, otherwise
}

mountain_wrapper(l1 l2 ... ln) = {
    mountain(l1 l2 ... ln, 0), if l1 < l2
    false, otherwise
}

process(l1 l2 ... ln) = {
    Ø, if n = 0
    remove_odd(l1) U process(l2 ... ln), if is_list(l1) AND mountain(l1)
    l1 U process(l2 ... ln), otherwise
}
```