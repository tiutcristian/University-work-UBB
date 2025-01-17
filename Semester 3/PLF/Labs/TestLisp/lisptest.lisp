; Given a list of length n of sublists representing work items
; and a list of length n of functions representing workers
; obtain the list of results of performing a work by each worker from their corresponding work item.

; e.g.: (work '(+ * -) '((2 3) (1 2) (7 5 1))) --> (5 2 1)

(DEFUN work (fl pl)
    (mapcar #'apply fl pl)
)

(print (work '(+ * -) '((2 3) (1 2) (7 5 1))))