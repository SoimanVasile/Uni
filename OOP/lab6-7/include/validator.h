#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "produs_tip.h"
#include <string>
class Validator{
    public:
        /**
         * @brief Default constructor for Validator
         */
        Validator() = default;

        /**
         * @brief Validates the properties of a product
         * 
         * @param name Name of the product
         * @param producator Producer of the product
         * @param tip Type of the product
         * @param pret Price of the product
         * @throws ValidatorException if validation fails
         */
        void validare_produs(const std::string& name,const std::string& producator,const ProdusTip tip,const float pret);
};

class ValidatorException{
private:
    std::string mesaj_eroare;
public:
    /**
     * @brief Construct a new Validator Exception object
     * 
     * @param mesaj The validation error message
     */
    ValidatorException(std::string mesaj) : mesaj_eroare(mesaj) {}
    
    /**
     * @brief Gets the exact validation error message
     * 
     * @return std::string The error message
     */
    std::string get_mesaj() const { return mesaj_eroare; }
};
#endif
