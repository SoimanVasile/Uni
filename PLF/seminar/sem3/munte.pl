descrescator([_]) :- !.
descrescator([H | [H2 | T]]) :- H > H2, !, descrescator( [H2 | T] ).

munte_aux( [H | [H2 | T]]) :- H < H2, !, munte_aux( [ H2 | T ] ).
munte_aux( [ _ | T ] ) :-  descrescator(T).

munte( [H | [ H2 | T]]) :- H < H2,  munte_aux( [H2 | T]).
