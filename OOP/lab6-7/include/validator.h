#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "produs_tip.h"
#include <string>
class Validator{
    public:
        Validator() = default;
        void validare_produs(const std::string& name,const std::string& producator,const ProdusTip tip,const float pret);
};

class ValidatorException{
private:
    std::string mesaj_eroare;
public:
    ValidatorException(std::string mesaj) : mesaj_eroare(mesaj) {}
    
    std::string get_mesaj() const { return mesaj_eroare; }
};
#endif
