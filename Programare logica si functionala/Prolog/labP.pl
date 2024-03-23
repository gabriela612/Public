% candidat(L : lista, E : element)
% L - lista din care luam elementul
% E - elementul pe care il luam
% Modele de flux : (i,o) nedeterminist, (i,i) determinist
candidat([H | []], H) :- !.
candidat([H | _T], H).
candidat([_H | T], E) :-
    candidat(T, E).

% gen(L : lista, Rp : lista, N : nr. nat., In : nr. nat, R : list)
% L - lista initiala
% Rp - lista rezultata (construita) pana la pasul curent
% N - numarul de elemente a listei finale
% In - numarul de elemente din Rp
% R - rezultatul
% Modele de flux : (i, i, i, i, o) nedeterminist, (i, i, i, i, i) determinist
gen(_L, Rp, N, N, Rp) :- !.
gen(L, Rp, N, In, R) :-
    candidat(L, E),
    not(candidat(Rp, E)),
    In1 is In + 1,
    N > In,
    gen(L, [E | Rp], N, In1, R).

% aranj(L : lista, K : nr. nat, Rez : lista)
% L - lista pentru care facem aranjamentele
% K - luam aranjamentele de cate K
% Rez - lista rezultata
% Modele de flux : (i, i, o) determinist, (i, i, i) determinist
aranj(L, K, Rez) :-
    findall(Var, gen(L, [], K, 0, Var), Rez).
