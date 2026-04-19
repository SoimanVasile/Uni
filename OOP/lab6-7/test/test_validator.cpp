#include <cassert>
#include "validator.h"

void test_validator() {
    Validator v;
    try {
        v.validare_produs("", "", LACTATE, -5);
        assert(false);
    } catch(ValidatorException& e) {
        std::string err = e.get_mesaj();
        assert(err.find("Numele este gol!") != std::string::npos);
        assert(err.find("Producator este gol!") != std::string::npos);
        assert(err.find("Pretul trebuie sa fie pozitiv!") != std::string::npos);
    }
    v.validare_produs("n", "p", CARNE, 1);
}
