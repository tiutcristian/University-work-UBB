; b) Write a function to test if a linear list of integer numbers has a "valley" aspect 
; (a list has a valley aspect if the items decrease to a certain point and then increase. Eg. 10 8 6 17 19 20).
; A list must have at least 3 elements to fullfill this condition.

; valley(l1 l2 ... ln, F) = {
;     true, if n = 1, F = 1
;     valley(l2 ... ln, 0), if l1 > l2 AND F = 0
;     valley(l2 ... ln, 1), if l1 < l2 AND F = 0
;     valley(l2 ... ln, 1), if l1 < l2 AND F = 1
;     false, otherwise
; }

; valley_wrapper(l1 l2 ... ln) = {
;     valley(l1 l2 ... ln, 0), if l1 > l2
;     false, otherwise
; }

(defun valley (l f)
    (cond
        ((null (cdr l)) (if (= f 1) t nil))
        ((and (> (car l) (cadr l)) (= f 0)) (valley (cdr l) 0))
        ((and (< (car l) (cadr l)) (= f 0)) (valley (cdr l) 1))
        ((and (< (car l) (cadr l)) (= f 1)) (valley (cdr l) 1))
        (t nil)
    )
)

(defun valleyw (l)
    (if (> (car l) (cadr l))
        (valley l 0)
        nil
    )
)


; Tests
(print (valleyw '(10 8 6 17 19 20)))    ; true

(print (valleyw '(10 8 6 17 19 20 18))) ; false

(print (valleyw '(10 8 6 5)))           ; false

(print (valleyw '(10 18 26 35)))        ; false

(print (valleyw '(10 18 6)))            ; false

(print (valleyw '(10 8 16)))            ; true