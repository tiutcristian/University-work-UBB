(DEFUN remDiv3 (l)
    (cond
        ((and (numberp l) (equal (mod l 3) 0)) nil)
        ((atom l) (list l))
        (t (list (mapcan #'remdiv3 l)))
    )
)

(defun remW (l)
    (car (remdiv3 l))
)


(print (remw '(6 1 2 3 (6) 4 5)))