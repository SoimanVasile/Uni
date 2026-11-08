paranteze(0, 0, []):- !.

paranteze(Nr_L, Nr_R, [ "(" | S ]) :- Nr_L > 0,
    Nr_L1 is Nr_L - 1,
    paranteze(Nr_L1, Nr_R, S).

paranteze(Nr_L, Nr_R, [ ")" | S ]) :- Nr_R > Nr_L,
    Nr_R1 is Nr_R - 1, !, 
    paranteze(Nr_L, Nr_R1, S).

generate_paranteze(N, S) :-
    paranteze(N, N, S).
