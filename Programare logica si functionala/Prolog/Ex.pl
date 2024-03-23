
candidat([H | _T], H).
candidat([_H | T], El) :- candidat(T, El).

aranj(_L, 0, []).
aranj(L, K, [El | Rez]) :-
    K > 0,
    K1 is K - 1,
    aranj(L, K1, Rez),
    candidat(L, El),
    not(candidat(Rez, El)).


comb([H | _T], 1, [H]).
comb([_H | T], K, Rez) :-
    comb(T, K, Rez).
comb([H | T], K, [H | Rez]) :-
    K > 1,
    K1 is K - 1,
    comb(T, K1, Rez).


len([], 0).
len([_H | T], Rez) :-
    len(T, Rp),
    Rez is Rp + 1.

perm(L, Rez) :-
    len(L, Len),
    aranj(L, Len, Rez).


subm([], []):- !.
subm([H | T], [H | Rez]) :- subm(T, Rez).
subm([_H | T], Rez) :- subm(T, Rez).



main(L, Rez) :-
    findall(Var, subm(L, Var), Rez).

















