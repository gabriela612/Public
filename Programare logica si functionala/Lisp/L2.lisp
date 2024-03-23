
; par(arb : lista, nrni : nr. nat, nrndp : nr. nat, st : lista)
; arb - arborele pe care il parcurgem
; nrni - numarul de noduri intalnite pana acum
; nrndp - numarul de noduri de parcurs (numarul de noduri pe care stim ca trebuie sa le parcurgem pentru a ajunge la fiul drept (daca exista))
; nodurile din fiul stang vizitate pana acum
(defun par(arb nrni nrndp st)
   (cond ((null arb) (list st arb))
   ( (= nrni nrndp) (list st arb))
   (t (par (cdr (cdr arb)) (+ 1 nrni) (+ (car (cdr arb)) nrndp) (append st (list (car arb) (car (cdr arb))))))
 )
)


; ino(arb : lista)
; arb - arborele pe care il parcurgem
(defun ino(arb)
   (cond ((null arb) nil)
   ( (equal (car (cdr arb)) 0) arb )
   ( t ( append (ino (car (par (cddr arb) '0 '1 '()))) (list (car arb) (car (cdr arb))) (ino (car (cdr (par (cddr arb) '0 '1 '())))) ) )
)
)