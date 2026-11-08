is_in_set([E|_], E) :- !.
is_in_set([H|T], E) :- H =\= E, is_in_set(T, E).

dif([], [_|_], []) :- !.
dif([H|T], B, F) :-
        is_in_set(B, H),
        dif(T, B, F).

dif([H|T], B, [H|F1]) :- \+ is_in_set(B, H),
        dif(T, B, F1).

