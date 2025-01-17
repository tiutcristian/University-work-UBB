(DEFUN F (X &OPTIONAL Y)
    (COND 
        ((NULL Y) (CDR X))
        (T (CONS (CAR X) Y))
    )
)


(print (append 
    (F '(1 2))
    (F '(3 4) '(5 6))
))