% likes(popa, ccn).
is_gay(popa).
male(popa).

has_dick(ccn).

loves_dick(X) :- is_gay(X),
    male(X).

likes( Person1, Person2 ) :- Person1 \= Person2,
    loves_dick(Person1), has_dick(Person2).
    
