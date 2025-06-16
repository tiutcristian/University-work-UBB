(defun g (l)
  (cond
    ((null l) nil)
    (t ((lambda (v)
          (cons (car v) (cadr v))
        )
        (f l)
       )
    )
  )
)

(print (g '(1 2 3 4 5 6 7 8 9 10)))

