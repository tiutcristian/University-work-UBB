; A linear list is given. Eliminate from the list all elements from N to N steps, N-given.

(defun remove_nth (l n c)
    (cond
        ((null l) nil)
        ((= (mod c n) 0) (remove_nth (cdr l) n (+ c 1)))
        (t (cons (car l) (remove_nth (cdr l) n (+ c 1))))
    )
)

(defun remove_nthw (l n)
    (remove_nth l n 1)
)

; Tests
(print (remove_nthw '(1 2 3 4 5 6 7 8 9 10) 3)) ; (1 2 4 5 7 8 10)

(print (remove_nthw '(1 2 3) 3))                ; (1 2)

(print (remove_nthw '(1 2) 3))                  ; (1 2)

(print (remove_nthw '() 3))                     ; NIL