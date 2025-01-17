# Seminar 4: Backtracking  

## Backtracking basics
- subsets
```
subset(l1l2...ln) = {
    Ø, if n = 0
    l1 U subset(l2...ln), if n > 0
    subset(l2...ln), if n > 0
}
```
- combinations
```
comb(l1l2...ln, k) = {
    l1, if k = 1
    l1 U comb(l2...ln, k - 1), if k > 1
    comb(l2...ln, k), if k >= 1
}
```
- permutations
```
insertEl(e, l1l2..ln) = {
    e U l1l2...ln, if n >= 0
    l1 U insertEl(e, l2...ln), if n > 0
}

perm(l1l2...ln) = {
    Ø, if n = 0
    insertEl(l1, perm(l2...ln)), if n > 0
}
```
- arrangements
```
arr(l1l2...ln, k) = {
    l1, if k = 1
    arr(l2...ln, k), if k >= 1, n > 0
    insertEl(l1, arr(l2...ln, k - 1)), if k > 1, n > 0
}
```


## Problems

### 1
Given a list L, generate the list of all arrangements of K elements from the list that have the sum S and product P.

```
onesol(L-list, K-number, S-number, P-number) = a1a2...ak, 
    if a1a2...ak=arr(L,K) 
    and suma(a1a2...ak)=S 
    and prod(a1a2...ak)=P

mainAllSol(L, K, S, P) = findAll(oneSol(L, K, S, P))
```

### 2
Given a sequence a1a2...an, composed of distinct integer numbers, display all subsequences with a valley shape.

```
valley(l1l2...ln, F) = {
    True, if n = 1, F = 1
    valley(l2...ln, 0), if l1 > l2 and F = 0
    valley(l2...ln, 1), if l1 < l2 and F = 1
    False, otherwise
}

main_valley(l1l2...ln) = {
    valley(l1l2...ln, 0), if l1 > l2
    false, otherwise
}

oneSol(l1l2...ln) = p1p2...pn, if 
        p1p2...pm = perm(subset(l1l2...ln))
        and valley(p1p2...pm)

mainAllSol(l1l2...ln) = findAll(oneSol(l1l2...ln))
```