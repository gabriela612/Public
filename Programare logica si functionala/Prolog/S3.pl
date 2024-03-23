

candidat([_H | T], Rez) :- candidat(T, Rez).
candidat([H | _T], H).

sterge([], _El, []) :- !.
sterge([H | T], H, Rez) :- sterge(T, H, Rez), !.
sterge([H | T], El, [H | Rez]) :- sterge(T, El, Rez), !.

% var2 : calculez lungimea si fac aranjamente de n luate cate n


% var1 : merg cu o variabila de rezultate curent cu functie speciala
% pentru diferenta (la inceput rezultatul curent e lista vida si nu pot
% verifica)
dif([], _El).
dif([H | _T], El) :-
    2 >= H - El,
    H >= El, !.
dif([H | _T], El) :-
    2 >= El - H,
    El > H, !.


perm([], Rez, Rez).
perm(L, Rc, Rez) :-
    candidat(L, El),
    not(candidat(Rc, El)),
    sterge(L, El, Lu),
    dif(Rc, El),
    perm(Lu, [El | Rc], Rez).


/* cod normal pentru PERMUTARI
perm([], Rez, Rez).
perm(L, Rezc, Rez) :-
    candidat(L, El),
    not(candidat(Rezc, El)),
    sterge(L, El, Lu),
    perm(Lu, [El | Rezc], Rez).
*/
