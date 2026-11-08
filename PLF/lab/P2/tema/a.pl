
% merge( List, List, Rez) - (i, i, o).
merge([H, H | T], L2, S) :- !, merge([H | T], L2, S).
merge(L1, [H, H | T], S) :- !, merge(L1, [H | T], S).

merge([H1 | T1], [H2 | T2], [H1 | S]) :- H1 < H2, !, merge(T1, [H2 | T2], S).
merge([H1 | T1], [H2 | T2], [H2 | S]) :- H1 > H2, !, merge([H1 | T1], T2, S).

merge([H1 | T1], [H1 | T2], [H1 | S]) :- !, merge(T1, T2, S).

merge([H | T], [], [H | S]) :- !, merge(T, [], S).
merge([], [H | T], [H | S]) :- !, merge([], T, S).
merge([], [], []) :- !.

% merge_list(List, Rez) - (i, o).
merge_list( [], []):- !.
merge_list([H | T], S) :- is_list(H), !, merge_list(T, S1), merge(H, S1, S).
merge_list( [ _ | T], S) :- !, merge_list(T, S).

