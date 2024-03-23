
prim(N) :- pr(N, 2).

pr(N, N) :- !.


pr(N, D) :-
    Rez is N mod D,
    Rez =\= 0,
    N > 2,
    D2 is D + 1,
    pr(N, D2), !.


add_final([], [], []) :- !.
add_final([Hi | Ti], La, [Hi | R]) :-
    add_final(Ti, La, R), !.

add_final([], [Ha | Ta], [Ha | R]) :-
    add_final(Ta, [], R), !.

divi_main(N, Rez) :-
    divi(N, Rez, 1).

divi(N, [N], N):- !.

divi(N, Rez, D) :-
    Rest is N mod D,
    Rest =\= 0,
    D1 is D + 1,
    divi(N, Rez, D1), !.

divi(N, [D | Rez], D) :-
    Rest is N mod D,
    Rest =:= 0,
    D1 is D + 1,
    divi(N, Rez, D1), !.

fc_main(L, Rez) :-
    fc(L, [], Rez).


fc([], [RezC], [RezC]).
fc([H | T], [RezC], [Rez]) :-
    prim(H),
    Rh is [H | RezC],
    %divi_main(H, Divi),
    %add_final(Rh, Divi, RezCu),
    fc(T, Rh, Rez), !.

fc([H | T], [RezC], [Rez]) :-
    not(prim(H)),
    Rh is [H | RezC],
    fc(T, Rh, Rez), !.



fct([], []) :- !.
fct([H | T], [H | Rez]) :-
    prim(H),
    divi_main(H, Divi),
    fct(T, RezP),
    add_final(RezP, Divi, Rez), !.
fct([H | T], [H | Rez]) :-
    not(prim(H)),
    fct(T, Rez), !.







