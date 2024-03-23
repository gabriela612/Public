

(defun f(x y)
(cond
   (t (format nil "Salut ~A si ~A!" x y))
))

(defun f(x)
(cond
   (t (format nil "Salut ~A!" x))
))


(defun apartine(a n)
(cond
   ((null a) NIL)
   ((equal (car a) n) 1)
   ((atom (car a)) (apartine (cdr a) n))
   (t (or (apartine (car a) n) (apartine (cdr a) n)))
))

(defun ap2(a el)
(cond
   ((atom a) NIL)
   ((equal (car a) el) 1)
   (t (or (ap2 (cadr a) el) (ap2 (caddr a) el) ) )
))


(defun ap3(l el)
(cond
   ((null l) NIL)
   ((listp (car l)) (or (ap3 (car l) el) (ap3 (cdr l) el) ))
   ((equal (car l) el) t)
   (t (ap3 (cdr l) el))
))


(defun path(a elem)
(cond
   ((null a) NIL)
   ((equal (car a) elem) (list elem))
   ((atom a) NIL)
   ((apartine (cadr a) elem) (cons (car a) (path (cadr a) elem)) )
   ((apartine (caddr a) elem) (cons (car a) (path (caddr a) elem)) )
))


(defun nivel(a elem niv)
(cond
   ((null a) NIL)
   ((equal (car a) elem) niv)
   ((apartine (cadr a) elem) (nivel (cadr a) elem (+ 1 niv)))
   ((apartine (caddr a) elem) (nivel (caddr a) elem (+ 1 niv)))
))


(defun get_niv(a niv)
(cond
   ((null a) NIL)
   ((equal niv 0) (list (car a)) )
   ((> niv 0) (append (get_niv (cadr a) (- niv 1)) (get_niv (caddr a) (- niv 1))) )
))

(defun len(a cl)
(cond
   ((null a) cl)
   (t (len (cdr a) (+ 1 cl)))
))

(defun get_niv_mx(a niv mx nivmx)
(cond
   ((null a) nivmx)
   ((equal (len (get_niv a niv) 0) 0) nivmx)
   ((> mx (len (get_niv a niv) 0)) (get_niv_mx a (+ 1 niv) mx nivmx))
   (t (get_niv_mx a (+ 1 niv) (len (get_niv a niv) 0) niv ))

))









