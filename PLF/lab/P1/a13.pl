is_in([H|_],H) :- !.

is_in([_|T], Elem) :- is_in(T, Elem).

make_set([], []) :- !.

make_set([H|T], [H|S1]) :- make_set(T, S1),
        \+ is_in(S1, H),
        !.

make_set([_|T], S) :- make_set(T, S).
