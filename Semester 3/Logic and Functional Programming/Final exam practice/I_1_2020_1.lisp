(DEFUN F (L)
    (COND
        ((NULL L) NIL)
        ((LISTP (CAR L)) (APPEND (F (CAR L)) (F (CDR L)) (CAR (F (CAR L)))))
        (T (LIST(CAR L)))
    )
)


(DEFUN F2 (L)
    (COND
        ((NULL L) NIL)
        ((LISTP (CAR L))
            ((lambda (p)
                (APPEND p (F (CDR L)) (CAR p))
            )
            (F (CAR L)))
        )
        (T (LIST(CAR L)))
    )
)


(print (F '(a b c)))
(print (F2 '(a b c)))