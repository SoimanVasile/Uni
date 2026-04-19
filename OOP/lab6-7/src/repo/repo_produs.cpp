#include <vector>

#include "MyList.h"
#include "repo_produs.h"
#include "attribute_produs.h"
#include "domain_produs.h"

bool equal_produs(const Produs& produs1, const Produs& produs2){
    return produs1.get_nume() == produs2.get_nume() && produs1.get_producator() == produs2.get_producator();
}

void RepoProdus::add_produs(const Produs& produs){
    if (lista_produse.find_elem(produs, [](const Produs& produs1, const Produs& produs2) -> bool {
                return equal_produs(produs1, produs2);
                })){
        throw RepoException("Acest produs exista deja!\n");
    }
    
    lista_produse.push(produs);
}

size_t RepoProdus::size() const{
    return lista_produse.size();
}

void RepoProdus::sterge_produs(const std::string& nume, const std::string& producator){
    AttributeProdus attrib(nume, producator);
    Produs produs(attrib, CARNE, 2.0);
    if (lista_produse.remove_elem(produs, [](const Produs& produs1, const Produs& produs2) -> bool {
                return equal_produs(produs1, produs2);})){
        return;
    }
    throw RepoException("Nu exista produsu!\n");
}

void RepoProdus::modifica_produs(const Produs& produs){
    if (lista_produse.modifica_elem(produs, [](const Produs& produs1, const Produs& produs2) -> bool{
                return equal_produs(produs1, produs2);
                })){
        return;
    }
    throw RepoException("Nu exista produsu!\n");
}

const Produs& RepoProdus::find_dupa_index(size_t i) const{
    if (i>=lista_produse.size())
        throw RepoException("Idexul este invalid!\n");
    return this->lista_produse.find_index(i);
}

const Produs& RepoProdus::find_dupa_nume_si_producator(const std::string& nume, const std::string& producator) const{
    AttributeProdus attrib(nume, producator);
    Produs produs(attrib, CARNE, 2.0);

    const Produs* produs_found = lista_produse.find_elem(produs, [](const Produs& produs1, const Produs& produs2)->bool {
                return equal_produs(produs1, produs2);
                });
    if (produs_found != nullptr){
        return *produs_found;
    }

    throw RepoException("Nu exista produsu!\n");

}

const MyList<Produs>& RepoProdus::get_all() const{
    return lista_produse.get_list();
}
