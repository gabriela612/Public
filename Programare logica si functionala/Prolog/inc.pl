

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


col_in(L, Rez) :-
    col(L, [], Rez).

col([], Rp, Rp) :- !.

col([H | T], Rp, Rez) :-
    %Rest is H mod 2,
    %Rest \== 0,
    prim(H),
    add_final(Rp, [H], Rp1),
    %Rp1 = [H | Rp],
    col(T, Rp1, Rez).

col([H | T], Rp, Rez) :-
    %Rest is H mod 2,
    %Rest == 0,
    not(prim(H)),
    add_final(Rp, [H], Rp1),
    divi_main(H, Divi),
    add_final(Rp1, Divi, Rp2),
    col(T, Rp2, Rez).




cmmdc(A, 0, A) :- !.
cmmdc(A, B, Rez) :-
    C is A mod B,
    cmmdc(B, C, Rez).

cmmmc(A, B, Rez) :-
    cmmdc(A, B, DC),
    Rez is A * B / DC.





