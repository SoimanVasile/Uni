suma_div(N, D, 0) :- D > N.

suma_div(N, D, S) :-
    N mod D =:= 0,
    D =< N,
    D1 is D + 1,
    suma_div(N, D1, S1),
    S is S1 + D.

suma_div(N, D, S) :-
    N mod D =\= 0,
    D =< N,
    D1 is D + 1,
    suma_div(N, D1, S).

init_suma(N, S) :- suma_div(N, 1, S).
