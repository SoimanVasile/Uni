#include <iostream>

#include "repo_produs.h"

void RepoProdus::add_produs(const Produs& produs){
    lista_produse.push_back(produs);
}

void RepoProdus::print(){
    for (Produs produs : lista_produse){
        std::cout<<produs<<' ';
    }
}

size_t RepoProdus::size(){
    return lista_produse.size();
}
