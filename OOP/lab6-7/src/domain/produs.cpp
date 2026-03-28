#include <iostream>

#include "attribute_produs.h"
#include "domain_produs.h"
#include "produs_tip.h"

Produs::Produs(AttributeProdus& attribute) : attrib(attribute) {}

std::string Produs::get_nume() const {
    return attrib.get_nume();
}

std::string Produs::get_producator() const {
    return attrib.get_producator();
}

float Produs::get_pret() const {
    return attrib.get_pret();
}

ProdusTip Produs::get_tip() const {
    return attrib.get_tip();
}

void Produs::set_nume(std::string& nume_nou){
    attrib.set_nume(nume_nou);
}

void Produs::set_producator(std::string& producator_nou) {
    attrib.set_producator(producator_nou);
}

void Produs::set_pret(float pret_nou) {
    attrib.set_pret(pret_nou);
}

void Produs::set_tip(ProdusTip tip_nou){
    attrib.set_tip(tip_nou);
}

std::ostream& operator<<(std::ostream& stream, const Produs& produs) {
    stream << "| Nume: " << produs.get_nume() 
           << " | Producator: " << produs.get_producator() 
           << " | Tip: " << produs.get_tip() 
           << " | Pret: " << produs.get_pret() << " |\n";
    return stream;
}
