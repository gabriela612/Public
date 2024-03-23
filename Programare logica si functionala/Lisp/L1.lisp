; sel(l : lista, k : intreg)
; l - lista din care luam al k-lea element
; k - pozita elementului pe care il luam din lista
(defun sel (l k)
    (cond ((NULL l) NIL)
    ((equal k 1) (car l))
    (t (sel (cdr l) (- k 1)))
)
)

; fi(l : lista, e : atom)
; l - lista in care cautam
; e - atomul cautat
(defun fi (l e)
    (cond ((NULL l) NIL)
    ( (and (atom (car l)) (equal (car l) e)) t )
    ( (and (atom (car l)) (not (equal (car l) e))) (fi (cdr l) e) )
    ( (list (car l)) (or (fi (car l) e) (fi (cdr l) e)) )
)
)

; subl(l : lista)
; l - lista pentru care cautam (si apelam msubl pentru) elemente care sunt liste
(defun subl (l)
    (cond ((NULL l) NIL)
    ((atom (car l)) (subl (cdr l)))
    ( (list (car l)) (append (msubl (car l)) (subl (cdr l))) )
)
)

; msubl(l: lista)
; l - lista la care ii punem in lista rezultat toate sublistele
(defun msubl (l)
    (cond ((NULL l) NIL)
    (t (append (list l) (subl l)))

)
)

; mul(l : lista)
; l - lista pe care o transformam intr-o multime
(defun mul (l)
    (cond ( (NULL l) NIL )
    ( (fi (cdr l) (car l)) (mul (cdr l)) )
    ( t (cons (car l) (mul (cdr l))) )
)
)





