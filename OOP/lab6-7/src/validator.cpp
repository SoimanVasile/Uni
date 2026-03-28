#include "validator.h"

void Validator::validare_produs(std::string& name, std::string& producator, ProdusTip tip, float pret){
    std::string error = "";
    if (name.empty()){
        error += "Numele este gol!\n";
    }

    if (producator.empty()){
        error += "Producator este gol!\n";
    }

    if (pret < 0){
        error += "Pretul trebuie sa fie pozitiv!\n";
    }

    (void)tip;

    if (error.size() != 0){
        throw ValidatorException(error);
    }
}
