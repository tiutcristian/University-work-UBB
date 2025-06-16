; 13. Define a function that returns the depth of a tree represented as 
; (root list_of_nodes_subtree1 ... list_of_nodes_subtreen)
; Eg. the depth of the tree (a (b (c)) (d) (e (f))) is 3

(defun find_max (l)
    (cond
        ((null l) nil)
        ((null (cdr l)) (car l))
        ((> (car l) (find_max (cdr l))) (car l))
        (t (find_max (cdr l)))
    )
)

; depth(tree) = {
;   0, if tree = nil
;   1, if atom(tree)
;   1, if null(cdr(tree))
;   1 + max(depth(list_of_nodes_subtree1), ..., depth(list_of_nodes_subtreen)), otherwise
(defun depth (tree)
    (cond
        ((null tree) 0)
        ((atom tree) 1)
        ((null (cdr tree)) 1)
        (t (+ 1 (find_max (mapcar #'depth (cdr tree))) )
        )
    )
)



; Tests
; Example tree: (a (b (c)) (d) (e (f)))
;      a
;     /|\
;    b d e
;   /     \
;  c       f
(print (depth '(a (b (c)) (d) (e (f))))) ; 3

; Null tree
(print (depth nil)) ; 0

; Atom
(print (depth 'a)) ; 1

; Single node tree
(print (depth '(a))) ; 1