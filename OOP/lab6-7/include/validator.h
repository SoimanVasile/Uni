#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "produs_tip.h"
#include <string>
class Validator{
    public:
        Validator() = default;
        void validare_produs(std::string& name, std::string& producator, ProdusTip tip, float pret);
};

class ValidatorException{
private:
    std::string mesaj_eroare;
public:
    ValidatorException(std::string mesaj) : mesaj_eroare(mesaj) {}
    
    std::string get_mesaj() const { return mesaj_eroare; }
};
#endif
