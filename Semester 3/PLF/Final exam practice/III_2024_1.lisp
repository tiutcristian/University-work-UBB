(defun subst_odd_lvl (e e1 l)
    (cond
        ((atom l) l)
        ((AND (atom (car l)) (equal e (car l))) 
            (cons e1 (subst_odd_lvl e e1 (cdr l))))
        ((atom (car l)) 
            (cons (car l) (subst_odd_lvl e e1 (cdr l))))
        (T (cons (MAPCAR (LAMBDA (L) (subst_odd_lvl e e1 L)) (car l)) (subst_odd_lvl e e1 (cdr l))))
    )
)


; (print (subst_odd_lvl 'a 'b '(a (a (a) (b a) (b b (a a b (a)))) a)))


(defun substitute-odd (lst e el &optional (level 0))
  (cond
    ((and (atom lst) (equal lst e) (oddp level)) el)
    ((atom lst) lst) 
    (t (mapcar (lambda (x) (substitute-odd x e el (1+ level))) lst))
  )
)

(print (substitute-odd '(a (a (a) (a a) (a a (a a a))) a) 'a 'b))