
(defun suma(l)
(cond
   ((null l) 0)
   (t (apply #'+ (mapcar #'(lambda (el) el) l)) )
))


(defun pr5(l)
(cond
   ((null l) 0)
   ((and (numberp l) (equal 5 l)) 1)
   ((and (numberp l) (not (equal 5 l))) 0)
   ((atom l) )
))


(defun liniara(l)
(cond
   ((null l) nil)
   ((atom (car l)) (cons (car l) (liniara (cdr l))))
   (t (append (liniara (car l)) (liniara (cdr l)) ))
))






(DEFUN F(L1 L2)
  (APPEND (F (CAR L1) L2)
          (COND
            ((NULL L1) (CDR L2))
            (T (LIST (F (CAR L1) L2) (CAR L2)))))
)


(defun find(a nod)
(cond
   ((and (atom a) (equal a nod)) nod)
   ((atom a) nil)
   ((equal (car a) nod) (list nod))
   ((not (mapcan #'(lambda (n) (find n nod)) a)) nil)
   (t (cons (car a) (mapcan #'(lambda (n) (find n nod)) a)))
))

