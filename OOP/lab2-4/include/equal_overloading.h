#ifndef EQUAL_OVERLOADING_H
#define EQUAL_OVERLOADING_H

#include "participant.h"
int equalcpcp(char* x, char* y);

int equalipip(int* x, int* y);

int equalPpPp(Participant* x, Participant* y);

void TYPE_MISMATCH_ERROR(void);

#define equal(x,y) _Generic((x),       \
    char*: _Generic((y),               \
        char*: equalcpcp,              \
        default: TYPE_MISMATCH_ERROR   \
        ),                             \
    int*: _Generic((y),                \
        int*: equalipip,               \
        default: TYPE_MISMATCH_ERROR   \
        ),                             \
    Participant*: _Generic((y),        \
        Participant* :equalPpPp,       \
        default: TYPE_MISMATCH_ERROR   \
        ),                             \
    default: TYPE_MISMATCH_ERROR       \
        )(x,y)

#endif
