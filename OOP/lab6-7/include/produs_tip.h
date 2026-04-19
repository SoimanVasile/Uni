#ifndef PRODUS_TIP_H
#define PRODUS_TIP_H

#include <iostream>
#include <string>
enum ProdusTip{
    LACTATE,
    CARNE,
    DULCIURI,
    CURATENIE,
};

class ProdusTipExpection {
    private:
        std::string eroare;

    public:
        ProdusTipExpection(std::string error) : eroare(error) {}

        std::string mesaj() const{
            return eroare;
        }
};

std::istream& operator>>(std::istream& stream, ProdusTip& produs);

std::ostream& operator<<(std::ostream& stream, const ProdusTip& produs);

#endif
