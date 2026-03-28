#include <string>

#include "attribute_produs.h"
#include "produs_tip.h"

AttributeProdus::AttributeProdus(std::string n, std::string prod, ProdusTip t, float p) : nume(n), producator(prod), tip(t), pret(p) {}

std::string AttributeProdus::get_nume() const {
    return nume;
}

std::string AttributeProdus::get_producator() const {
    return producator;
}

float AttributeProdus::get_pret() const {
    return pret;
}

ProdusTip AttributeProdus::get_tip() const {
    return tip;
}

void AttributeProdus::set_nume(std::string& nume_nou){
    nume = nume_nou;
}

void AttributeProdus::set_producator(std::string& producator_nou){
    producator = producator_nou;
}
void AttributeProdus::set_pret(float pret_nou){
    pret = pret_nou;
}
void AttributeProdus::set_tip(ProdusTip tip_nou){
    tip = tip_nou;
}
