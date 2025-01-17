; Sã se stearga dintr-o listà neliniara toate sublistele (liniare) care au numär par de elemente.
; , De exemplu:
; # (sterg' ((2 3 4) (6 (7 8) ((7 9) 8) (68) 9) → ((2 3 4) (6 (8)) 9)

(DEFUN stergere (L)
    (cond
        ((ATOM L) (LIST L))
        ((CHECK L) NIL)
        (T (LIST (MAPCAN #'stergere L)))
    )
)

(DEFUN REZ (L)
    (CAR (stergere L))
)

(DEFUN CHECK (L)
    (AND
        (EVAL 
            (APPEND 
                (LIST 'AND) 
                (MAPCAR #'ATOM L)
            )
        )
        (EQL 
            (MOD 
                (LENGTH L) 
                2
            ) 
            0
        )
    )
)

; (PRINT (CHECK '(A B C C)))


(PRINT (REZ '((2 3 4) (6 (7 8) ((7 9) 8) (6 8) 9)))) ; ((2 3 4) (6 (8)) 9)