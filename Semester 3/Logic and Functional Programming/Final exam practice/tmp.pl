(DEFUN F(L)
    (COND
        ((NULL L) 0)
        (> (F (CAR L)) 2) (+ (CAR L) (F (CDR L)))
        (T (F (CAR L)))
    )
)


(DEFUN F2(L)
    (COND
        ((NULL L) 0)
        (T 
            (lambda (p)
                (> p 2) (+ (CAR L) (F (CDR L)))
                (T p)
            ) (F (CAR L))
        )
    )
)