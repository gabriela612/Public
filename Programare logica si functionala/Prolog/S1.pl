
/*
Fie o lista numerica si urmatoarea definitie de predicat prolog f(list, integer), avand modelul de flux (i,o):
f([], -1).
f([H|T], S) :-H>0, f(T,S1),S1<H,!,S is H.
f([_|T],S):-f(T,S1), S is S1.
Rescrieti acesta definitie pentru a evita apelul recursiv in ambele clauze. Nu redefiniti predicatul. Justificati raspunsul.
*/
% aj(M1 : int, M2 : int, S : int)
% M1 - primul element
% M2 - al doilea element
% S - maximul dintre M1 si M2
% model de flux : (i,i,o), (i,i,i)
maxim(M1, M2, M1) :-
    M1 >= M2, !.
maxim(M1, M2, M2) :-
    M2 > M1, !.

f([], -1).
f([H | T], Sol) :-
    f(T, Solp),
    maxim(H, Solp, Sol), !.


/* problema 2*/


candidat([H | _], H).
candidat([_ | T], E) :- candidat(T, E).

aranj([_H | _T], 0, Rez, Rez).
aranj([H | T], K, RezC, Rez) :-
    candidat([H | T], El),
    not(candidat(RezC, El)),
    Ku is K - 1,
    aranj([H | T], Ku, [El | RezC], Rez).

produs([H | []], H).
produs([H | T], Rez) :-
    produs(T, Rezp),
    Rez is Rezp * H.

ar_pr([H | T], K, Prod, Rez) :-
    aranj([H | T], K, [], Rez),
    produs(Rez, Prod).

main(L, K, Prod, Rez) :-
    findall(Var, ar_pr(L, K, Prod, Var), Rez).


