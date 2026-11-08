cmmdc(A, A, S) :- !, S is A.

cmmdc(A, B, C) :- A > B, !,
    A1 is A - B,
    cmmdc(A1, B, C).

cmmdc(A, B, C) :- B1 is B - A,
    cmmdc(A, B1, C).

% cmmdc_list (i, o)
cmmdc_list([H|[]], H) :- !.

cmmdc_list([H|T], S) :- cmmdc_list(T, S1),
        cmmdc(H, S1, S).



