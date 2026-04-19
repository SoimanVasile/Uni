#include "produs_tip.h"
#include <algorithm>
#include <cctype>
#include <exception>

std::istream& operator>>(std::istream& stream, ProdusTip& tip) {
    std::string input;
    stream >> input;

    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if  (input == "lactate") {
        tip = ProdusTip::LACTATE;
    } else if (input == "carne") {
        tip = ProdusTip::CARNE;
    } else if (input == "dulciuri") {
        tip = ProdusTip::DULCIURI;
    } else if (input == "curatenie") {
        tip = ProdusTip::CURATENIE;
    } else {
        throw ProdusTipExpection("Nu exista acest tip!\n");
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
