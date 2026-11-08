cmmpl(A, B, C) :- cmmdc(A, B, C1),
        C is A * B / C1.

cmmdc(A, A, A).

cmmdc(A, B, C) :- A > B,
    A1 is A - B,
    cmmdc(A1, B, C).

cmmdc(A, B, C) :- A < B,
    B1 is B - A,
    cmmdc(A, B1, C).

cmmpl_list([], 1) :- !.

cmmpl_list([H|T], S) :- cmmpl_list(T, S1),
        cmmpl(H, S1, S).
