; myMax(a : elem, b : elem)
; - a : primul element pe care il consideram pentru maxim
; - b : al doilea element pe care il consideram pentru maxim
(defun myMax(a b)
  (cond
    ((and (not (numberp a)) (not (numberp b))) nil)
    ((not (numberp b)) a)
    ((not (numberp a)) b)
    ((> a b) a)
    (t b)
  )
)

; findMax(l : lista)
; l - lista pentru care returnam numarul maxim
(defun findMax(l)
  (cond
    ((null l) nil)
    (t (myMax (car l) (findMax (cdr l))))
  )
)

; ad(l : lista, counter : numar)
; l - arborele la care vrem sa ii aflam adancimea
; counter - adancimea curenta
(defun ad(l counter)
  (cond
    ((atom l) counter)
    (t (apply #'findMax (list (mapcar #' (lambda (a) (ad a (+ 1 counter))) l))))
  )
)

; adancime(l : lista)
; l - arborele la care vrem sa ii aflam adancimea
(defun adancime(l)
  (cond
    ((null l) NIL)
    (t (ad l 0))
))