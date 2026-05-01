#include <vector>

#include "repo_produs.h"
#include "attribute_produs.h"
#include "domain_produs.h"
#include <algorithm>

bool equal_produs(const Produs& produs1, const Produs& produs2){
    return produs1.get_nume() == produs2.get_nume() && produs1.get_producator() == produs2.get_producator();
}

void RepoProdus::add_produs(const Produs& produs){
    auto it = std::find_if(lista_produse.begin(), lista_produse.end(), [&produs](const Produs& p) {
        return equal_produs(produs, p);
    });
    if (it != lista_produse.end()) {
        throw RepoException("Acest produs exista deja!\n");
    }
    
    lista_produse.push_back(produs);
}

size_t RepoProdus::size() const{
    return lista_produse.size();
}

void RepoProdus::sterge_produs(const std::string& nume, const std::string& producator){
    AttributeProdus attrib(nume, producator);
    Produs produs(attrib, CARNE, 2.0);
    auto it = std::find_if(lista_produse.begin(), lista_produse.end(), [&produs](const Produs& p) {
        return equal_produs(produs, p);
    });
    if (it != lista_produse.end()) {
        lista_produse.erase(it);
        return;
    }
    throw RepoException("Nu exista produsu!\n");
}

void RepoProdus::modifica_produs(const Produs& produs){
    auto it = std::find_if(lista_produse.begin(), lista_produse.end(), [&produs](const Produs& p) {
        return equal_produs(produs, p);
    });
    if (it != lista_produse.end()) {
        *it = produs;
        return;
    }
    throw RepoException("Nu exista produsu!\n");
}

const Produs& RepoProdus::find_dupa_index(size_t i) const{
    if (i>=lista_produse.size())
        throw RepoException("Idexul este invalid!\n");
    return this->lista_produse.at(i);
}

const Produs& RepoProdus::find_dupa_nume_si_producator(const std::string& nume, const std::string& producator) const{
    AttributeProdus attrib(nume, producator);
    Produs produs(attrib, CARNE, 2.0);

    auto it = std::find_if(lista_produse.begin(), lista_produse.end(), [&produs](const Produs& p) {
        return equal_produs(produs, p);
    });
    if (it != lista_produse.end()) {
        return *it;
    }

    throw RepoException("Nu exista produsu!\n");

}

const std::vector<Produs>& RepoProdus::get_all() const{
    return lista_produse;
}
