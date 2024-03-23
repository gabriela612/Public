
a(1).
a(2).
b(1).
b(2).
c(1).
c(2).
s() :- a(X), b(_Y), c(_Z), !, write(X), nl. % => 1

% s() :- !, a(X), b(_Y), c(_Z), write(X), nl. % => 1 de 4 ori si 2 de
% patru ori
%

suma([], 0, 0) :- !.
suma([H | T], Rez, Len) :-
    suma(T, Rezp, Lenp),
    Len is Lenp + 1,
    Rez is Rezp + H, !.


subm([], []) :- !.
subm([_H | T], Rez) :- subm(T, Rez).
subm([H | T], [H | Rez]) :-
    subm(T, Rez).


mult_sum(L, N, Rez) :-
    subm(L, Rez),
    suma(Rez, S, Len),
    Len >= N,
    0 is S mod 3.

