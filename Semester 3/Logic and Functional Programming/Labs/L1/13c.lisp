; c) Build a function that returns the minimum numeric atom from a list, at any level.

; min_atom(l1...ln, m) = {
;   m, if l is empty
;   min_atom(l2...ln, l1), if l1 is number and (m = nil or l1 < m)
;   min_atom(l2...ln, m), if l1 is number and l1 >= m
;   min_atom(l2...ln, min_atom(l1, m)), if l1 is list
; }

(defun min_atom (l min)
    (cond
        ((null l) min)
        ((numberp (car l)) 
            (if (or (null min) (< (car l) min))
                (min_atom (cdr l) (car l))
                (min_atom (cdr l) min)
            )
        )
        ((listp (car l)) (min_atom (cdr l) (min_atom (car l) min)))
        (t (min_atom (cdr l) min))
    )
)
        

; test cases
(print (min_atom '(1 2 3 4 5 6 7 8 9 10) nil)) ; 1
(print (min_atom '(1 2 a 4 5 6 7 8 9 10) nil)) ; 1
(print (min_atom '(a 1 2 a 4 5 6 7 8 9 10) nil)) ; 1
(print (min_atom '(1 2 0 4 5 6 7 8 9 10) nil)) ; 0
(print (min_atom '((1 2 3) 4 5 6 7 8 9 10) nil)) ; 1
(print (min_atom '((1 a 3) 4 5 6 7 8 9 10) nil)) ; 1
(print (min_atom '(10 9 8 7 6 5 a 3 2 1) nil)) ; 1
(print (min_atom '(10 9 (8 7 6 5 4 3 2 1)) nil)) ; 1
(print (min_atom '(10 9 a (8 7 a 6 5 4 3 2 1)) nil)) ; 1