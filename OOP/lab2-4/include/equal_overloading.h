#ifndef EQUAL_OVERLOADING_H
#define EQUAL_OVERLOADING_H

#include "participant.h"
int equalcpcp(char* x, char* y);

int equalipip(int* x, int* y);

int equalPpPp(Participant* x, Participant* y);

#define equal(x,y) _Generic((x),\
    char*: equalcpcp((x),(y)),\
    int*: equalipip((x),(y)),\
    Participant*: equalPpPp((x),(y))\
        )

#endif
