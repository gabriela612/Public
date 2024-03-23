
%interclasare(La : lista, Lb : lista, Rez : lista)
%La = prima dintre cele doua liste pe care le interclasam
%Lb = a doua dintre cele doua liste pe care le interclasam
%Rez = lista rezultata interclasarii listelor La si Lb
% Modele de flux : (i,i,o) det, (i,i,i) det, (i,o,i) det, (o,i,i) det
interclasare([], [], []) :- !.
interclasare([H | T], [], [H | Rez]) :-
    interclasare(T, [], Rez), !.
interclasare([], [H | T], [H | Rez]) :-
    interclasare([], T, Rez), !.
interclasare([Ha | Ta], [Hb | Tb], [Ha | Rez]) :-
    interclasare(Ta, [Hb | Tb], Rez),
    Ha =< Hb, !.
interclasare([Ha | Ta], [Hb | Tb], [Hb | Rez]) :-
    interclasare([Ha | Ta], Tb, Rez),
    Hb < Ha, !.

%sortare_f(L : lista, Rezp : lista, Rez : lista)
%L = lista pe care o sortam
% Rezp = lista rezultata prin sortarea elementelor din lista initiala
% pana la pasul curent
% Rez = lista sortata
% Model de flux : (i,i,o) determinist, (i,i,i) determinist
sortare_f([], Rez, Rez) :- !.
sortare_f([H | T], Rezp, Rez) :-
    interclasare([H], Rezp, Rc),
    sortare_f(T, Rc, Rez), !.

%sortare_f(L : lista, Rez : lista)
%L = lista pe care o sortam
% Rez = lista sortata
% Modele de flux : (i,o) determinist, (i,i) determinist
sortare(Li, Rez) :-
    sortare_f(Li, [], Rez), !.








