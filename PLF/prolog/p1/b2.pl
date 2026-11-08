add_elem([], V, [V], CurElem, NextPower) :- CurElem =:= NextPower.
add_elem([], _, [], CurElem, NextPower) :- CurElem =\= NextPower.

add_elem([H|T], V, S, CurElem, NextPower) :- CurElem =:= NextPower,
         CE1 is CurElem + 1,
         NP1 is NextPower * 2,
         add_elem(T, V, S1, CE1, NP1),
         S = [H|[V|S1]].

add_elem([H|T], V, S, CurElem, NextPower) :- CurElem =\= NextPower,
        CE1 is CurElem + 1,
        add_elem(T, V, S1, CE1, NextPower),
        S = [H | S1].
    

add_elemV(L, V, S) :- add_elem(L, V, S, 1, 1).
