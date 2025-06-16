(defun f (l lvl)
    (cond
        ((numberp l) (* l lvl))
        ((atom l) l)
        (T (mapcar
            #'(LAMBDA (l1)
                (f l1 (1+ lvl))
            )
            l
        ))
    )
)


; (print (f '(a 1 ((5 b) 2 (3))) 0))