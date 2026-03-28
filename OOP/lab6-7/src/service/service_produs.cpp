#include <exception>

#include "validator.h"
#include "service_produs.h"
#include "attribute_produs.h"
#include "domain_produs.h"
#include "repo_produs.h"

ServiceProdus::ServiceProdus(RepoProdus& repo, Validator& validator) : repo_produs(repo), validator_produs(validator) {}

void ServiceProdus::add_produs(std::string nume, std::string producator, ProdusTip tip, float pret){
    validator_produs.validare_produs(nume, producator, tip, pret);

    AttributeProdus attrib(nume, producator, tip, pret);
    Produs produs_nou(attrib);

    repo_produs.add_produs(produs_nou);
}

void ServiceProdus::print(){
    repo_produs.print();
}
