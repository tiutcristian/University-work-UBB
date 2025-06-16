(defun find_left (tree nodes edges)
  (cond
   	((null tree) nil)
    ((= nodes (+ 1 edges)) nil)
    (t (cons (car tree) 
             (cons (cadr tree) 
                   (find_left (cddr tree) (+ 1 nodes) (+ (cadr tree) edges))
             )
       )
    )
  )
)

(defun left (tree)
  (find_left (cddr tree) 0 0)
)

(defun find_right (tree nodes edges)
  (cond
   	((null tree) nil)
    ((= nodes (+ 1 edges)) tree)
    (t (find_right (cddr tree) (+ 1 nodes) (+ (cadr tree) edges)))
  )
)

(defun right (tree)
  (find_right (cddr tree) 0 0)
)

; (print (left '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) ))
; (print (right '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) ))

(defun v2tov1 (tree)
  (cond
    ((null tree) nil)
    (t (list (car tree)
             (v2tov1 (left tree))
             (v2tov1 (right tree)) 
       )
    )
  )
)

(print (v2tov1 '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) ))