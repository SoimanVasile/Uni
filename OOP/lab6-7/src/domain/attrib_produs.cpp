#include <string>

#include "attribute_produs.h"

AttributeProdus::AttributeProdus(std::string n, std::string prod) : nume(n), producator(prod) {}

std::string AttributeProdus::get_nume() const {
    return nume;
}

std::string AttributeProdus::get_producator() const {
    return producator;
}
