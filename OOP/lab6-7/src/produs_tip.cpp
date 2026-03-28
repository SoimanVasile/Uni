#include "produs_tip.h"

std::istream& operator>>(std::istream& stream, ProdusTip& tip) {
    std::string input;
    stream >> input;

    if (input == "LACTATE" || input == "lactate") {
        tip = LACTATE;
    } else if (input == "CARNE" || input == "carne") {
        tip = CARNE;
    } else if (input == "DULCIURI" || input == "dulciuri") {
        tip = DULCIURI;
    } else if (input == "CURATENIE" || input == "curatenie") {
        tip = CURATENIE;
    } else {
        stream.setstate(std::ios::failbit); 
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const ProdusTip& tip) {
    switch (tip) {
        case LACTATE: stream << "LACTATE"; break;
        case CARNE: stream << "CARNE"; break;
        case DULCIURI: stream << "DULCIURI"; break;
        case CURATENIE: stream << "CURATENIE"; break;
    }
    return stream;
}
