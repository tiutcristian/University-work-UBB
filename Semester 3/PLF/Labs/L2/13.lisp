; 13. For a given tree of type (2) return the path from the root node to a certain given node X.
; Tree of type 2: (node (list-subtree-1) (list-subtree-2) ...)

(defun find_path (tree x)
    (cond
        ((null tree) nil)

        ((eq (car tree) x) 
            (list (car tree)))
        
        ((find_path (cadr tree) x)
            (cons (car tree) (find_path (cadr tree) x)))
        
        ((find_path (caddr tree) x)
            (cons (car tree) (find_path (caddr tree) x)))
        
        (t nil)
    )
)

; Tests
;       1
;      / \
;     2   3
;    / \
;   4   5
(print (find_path   '(1 (2 (4 nil nil) (5 nil nil)) (3 nil nil)) 
                    5)) ; (1 2 5)

(print (find_path   '(1 (2 (4 nil nil) (5 nil nil)) (3 nil nil)) 
                    3)) ; (1 3)

(print (find_path   '(1 (2 (4 nil nil) (5 nil nil)) (3 nil nil)) 
                    1)) ; (1)

(print (find_path   '(1 (2 (4 nil nil) (5 nil nil)) (3 nil nil)) 
                    6)) ; nil