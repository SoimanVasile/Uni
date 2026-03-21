#include <string.h>
#include <stdio.h>

#include "equal_overloading.h"

int equalcpcp(char* x, char* y){
    if (strlen(x) != strlen(y)){
        return 0;
    }

    for (size_t i=0; i<strlen(x); i++){
        if (x[i]!=y[i]) return 0;
    }

    return 1;
}

int equalipip(int *x, int *y){
    for (int i=0; i<10; i++){
        if (x[i]!=y[i]) return 0;
    }
    return 1;
}

int equalPpPp(Participant *x, Participant *y){
    if (!equalcpcp(x->nume, y->nume)) return 0;
    if (!equalcpcp(x->prenume, y->prenume)) return 0;

    return 1;
}
