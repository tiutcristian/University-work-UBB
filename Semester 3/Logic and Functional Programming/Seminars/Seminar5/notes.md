# Seminar 5

### 1. Define a function which merges, without keeping duplicates, two linear lists that are sorted in ascending order. Each list contains unique elements.

#### Mathematical model
```
merge(l1l2...ln, k1k2...km) = 
    l1l2...ln, if m = 0
    k1k2...km, if n = 0
    l1 U merge(l2...ln, k1k2...km), if l1 < k1
    k1 U merge(l1l2...ln, k2...km), if l1 > k1
    l1 U merge(l2...ln, k2...km), if l1 = k1
```

#### Lisp Implementation
```lisp
(defun merge (l1 l2)
    (cond
        ((null l1) l2)
        ((null l2) l1)
        ((< (car l1) (car l2)) (cons (car l1) (merge (cdr l1) l2)))
        ((> (car l1) (car l2)) (cons (car l2) (merge l1 (cdr l2))))
        (t (cons (car l1) (merge (cdr l1) (cdr l2))))
    )
)
```

### 2. Define a function to remove all the occurrences of an element from a non-linear list.

#### Mathematical model
```
remove(l1l2...ln, e) = 
    [], if n = 0
    remove(l2...ln, e), if l1 atom and l1 = e
    remove(l1, e) U remove(l2...ln, e), if l1 list
    l1 U remove(l2...ln, e), otherwise
```

#### Lisp Implementation
```lisp
(defun remove_occ (l e)
    (cond
        ((null l) nil)
        ((and (atom (car l)) (equal (car l) e)) (remove_occ (cdr l) e))
        ((listp (car l)) (cons (remove_occ (car l) e) (remove_occ (cdr l) e)))
        (t (cons (car l) (remove_occ (cdr l) e)))
    )
)

;; Test
(print (remove_occ '(1 2 (3 4) 5 6 (7 (3) 8 9) 10) 3))
;; Output: (1 2 (4) 5 6 (7 NIL 8 9) 10)
```

### Obs.:
- (print (equal '(1) 1)) => nil
- (print (equal 1 '(1))) => nil
- (print (= '(1) 1)) => Error

### 3. Build a list with the positions of the minimum number from a linear list. The list may contain non-numeric atoms.

#### Mathematical model
```
findMin(l1l2...ln, min) = {
    min, if n = 0
    findMin(l2...ln, l1), if l1 is number and (min = nil or l1 < min)
    findMin(l2...ln, min), otherwise
}

findPosOfMin(l1l2...ln, min, pos) = {
    [], if n = 0
    pos U findPosOfMin(l2...ln, min, pos + 1), if l1 = min
    findPosOfMin(l2...ln, min, pos + 1), otherwise
}
```

#### Lisp Implementation
```lisp
(defun find_min (l min)
    (cond
        ((null l) min)
        ((and (numberp (car l)) (or (null min) (< (car l) min))) (find_min (cdr l) (car l)))
        (t (find_min (cdr l) min))
    )
)

(defun find_pos_of_min (l min pos)
    (cond
        ((null l) nil)
        ((equal (car l) min) (cons pos (find_pos_of_min (cdr l) min (+ pos 1))))
        (t (find_pos_of_min (cdr l) min (+ pos 1)))
    )
)

(defun find_pos_list (l)
    (find_pos_of_min l (find_min l nil) 1)
)

;; Test
(print (find_pos_list '(a 8 9 z 3 7 7 3 q)))
;; Output: (5 8)
```

### 4. Add an element to a linear list after every n-th element.

#### Mathematical model
```
addAtN(l1l2...lm, pos, n, e) = {
    Ø, if m = 0
    l1 U e U (l2...lm, pos + 1, n, e), if pos mod n = 0
    l1 U addAtN(l2...lm, pos + 1, n, e), otherwise
}
```

#### Lisp Implementation
```lisp
(defun add_at_n (l pos n e)
    (cond
        ((null l) nil)
        ((= (mod pos n) 0) (cons (car l) (cons e (add_at_n (cdr l) (+ pos 1) n e))))
        (t (cons (car l) (add_at_n (cdr l) (+ pos 1) n e)))
    )
)

;; Test
(print (add_at_n '(1 2 3 4 5 6 7 8 9 10) 1 3 'x))
;; Output: (1 2 3 X 4 5 6 X 7 8 9 X 10)
```