#ifndef PRODUS_TIP_H
#define PRODUS_TIP_H

#include <iostream>
enum ProdusTip{
    LACTATE,
    CARNE,
    DULCIURI,
    CURATENIE,
};

std::istream& operator>>(std::istream& stream, ProdusTip& produs);

std::ostream& operator>>(std::ostream& stream, ProdusTip& produs);

#endif
