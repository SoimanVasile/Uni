#include <iostream>

#include "attribute_produs.h"
#include "domain_produs.h"
#include "produs_tip.h"

Produs::Produs(const AttributeProdus& attribute, const ProdusTip t, const float p) : attrib(attribute), tip(t), pret(p) {}

std::string Produs::get_nume() const {
    return attrib.get_nume();
}

std::string Produs::get_producator() const {
    return attrib.get_producator();
}

float Produs::get_pret() const {
    return pret;
}

ProdusTip Produs::get_tip() const {
    return tip;
}

void Produs::set_pret(float pret_nou) {
    pret = pret_nou;
}

void Produs::set_tip(ProdusTip tip_nou){
    tip = tip_nou;
}

std::ostream& operator<<(std::ostream& stream, const Produs& produs) {
    stream << "| Nume: " << produs.get_nume() << " | Producator: " << produs.get_producator() << " | Tip: " << produs.get_tip() << " | Pret: " << produs.get_pret() << " |\n";
    return stream;
}

bool Produs::operator==(const Produs& produs_1) const{
    return (produs_1.get_nume() == this->get_nume()) && (produs_1.get_producator() == this->get_producator());
}
