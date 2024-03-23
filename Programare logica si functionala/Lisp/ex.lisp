
; len(l : lista, lc : numar)
; l - lista la care ii numaram lungimea
; lc - lungimea curenta
(defun len(l lc)
(cond
   ((null l) lc)
   (t (len (cdr l) (+ 1 lc)))
))

; nr_par(l : lista)
; l - lista la care verificam sa aiba numar par de elemente
(defun nr_par(l)

   (equal (mod (len l 0) 2) 0)
)

; liniara(l : lista)
; l - lista pe care o verificam sa fie liniara
(defun liniara(l)
(cond
   ((null l) t)
   ((listp (car l)) NIL)
   (t (liniara (cdr l)))
))

; st(l : lista)
; l - lista pentru care eliminam sublistele liniare care au numar par de elemente
(defun st(l)
(cond
   ((null l) NIL)
   ((atom (car l)) (cons (car l) (st (cdr l))) )
   ((not (liniara (car l))) (append (list (st (car l))) (st (cdr l)) ) )
   ( (and (liniara (car l)) (nr_par (car l))) (st (cdr l)))
   ( (and (liniara (car l)) (not (nr_par (car l)))) ( append (list (car l)) (st (cdr l)) ) )

))







