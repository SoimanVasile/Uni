add_one([], []) :- !.
add_one([H|T], [H|F]) :- H mod 2 =:= 1,
        add_one(T,F).

add_one([H|T], F) :- H mod 2 =:= 0,
        add_one(T, F1) ,
        F = [H|[1|F1]].


