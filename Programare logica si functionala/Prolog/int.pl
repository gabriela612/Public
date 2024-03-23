
int([], [], []) :- !.
int([], [H | T], [H | Rez]) :-
    int([], T, Rez), !.
int([H | T], [], [H | Rez]) :-
    int(T, [], Rez), !.
int([Ha | Ta], [Hb | Tb], [Ha | Rez]) :-
    Ha =< Hb,
    int(Ta, [Hb | Tb], Rez), !.
int([Ha | Ta], [Hb | Tb], [Hb | Rez]) :-
    Ha > Hb,
    int([Ha | Ta], Tb, Rez), !.

ins([], Rp, Rp) :- !.
ins([H | T], Rp, Rez) :-
    int([H], Rp, Rpu),
    ins(T, Rpu, Rez).




sor(L, Rez) :-
    ins(L, [], Rez).
