; d) Write a function that deletes from a linear list all occurrences of the maximum element.

; find_max(l1l2...ln) = {
;   l1, if l1 > find_max(l2l3...ln)
;   find_max(l2l3...ln), otherwise
; }
(defun find_max (l)
    (cond
        ((null l) nil)
        ((null (cdr l)) (car l))
        ((> (car l) (find_max (cdr l))) (car l))
        (t (find_max (cdr l)))
    )
)

; delete_val(l1l2...ln v) = {
;   delete_max(l2...ln), l1 = v
;   l1 U delete_max(l2...ln), otherwise
; }
(defun delete_val (l e)
    (cond
        ((null l) nil)
        ((= (car l) e) (delete_val (cdr l) e))
        (t (cons (car l) (delete_val (cdr l) e)))
    )
)

(defun delete_max (l)
    (delete_val l (find_max l))
)


; Test cases:
(print (delete_max '(1 2 3 4 5 6 7 8 9 10))) ; (1 2 3 4 5 6 7 8 9)
(print (delete_max '(1 2 10 4 5 6 7 8 9 10))) ; (1 2 4 5 6 7 8 9)
(print (delete_max '(10 10 10))) ; nil
(print (delete_max '(10 3 10))) ; (3)