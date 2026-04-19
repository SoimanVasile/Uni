#include <algorithm>
#include <exception>
#include <string>

#include "produs_tip.h"
#include "validator.h"
#include "service_produs.h"
#include "attribute_produs.h"
#include "domain_produs.h"
#include "repo_produs.h"

ServiceProdus::ServiceProdus(RepoProdus& repo, Validator& validator) : repo_produs(repo), validator_produs(validator) {}

void ServiceProdus::add_produs(const AttributeProdus& attrib, ProdusTip tip, float pret){
    std::string nume = attrib.get_nume();
    std::string producator = attrib.get_producator();
    validator_produs.validare_produs(nume, producator, tip, pret);

    Produs produs_nou(attrib, tip, pret);

    repo_produs.add_produs(produs_nou);
}

MyList<Produs> ServiceProdus::get_all() const{
    return repo_produs.get_all();
}

void ServiceProdus::sterge_produs(const std::string& name, const std::string& producator){
    validator_produs.validare_produs(name, producator, CARNE, 2.0);

    repo_produs.sterge_produs(name, producator);
}

void ServiceProdus::modifica_produs(AttributeProdus& attrib, ProdusTip tip, float pret){
    std::string nume = attrib.get_nume();
    std::string producator = attrib.get_producator();
    validator_produs.validare_produs(nume, producator, tip, pret);

    Produs produs_nou(attrib, tip, pret);

    repo_produs.modifica_produs(produs_nou);
}

const Produs& ServiceProdus::find_dupa_nume_si_producator(const std::string& name, const std::string& producator) const{
    validator_produs.validare_produs(name, producator, CARNE, 2.0);

    return repo_produs.find_dupa_nume_si_producator(name, producator);
}

MyList<Produs> ServiceProdus::filtrare_dupa_pret(const float pret) const{
    MyList<Produs> lista_produs = repo_produs.get_all();
    MyList<Produs> filtrat;

    for (const Produs& produs : lista_produs){
        if (produs.get_pret() < pret)
            filtrat.push(produs);
    }
    return filtrat;
}

MyList<Produs> ServiceProdus::sortare_dupa_pret() const{
    MyList<Produs> lista = repo_produs.get_all();
    std::sort(lista.begin(), lista.end(), [](const Produs& pret_1, const Produs& pret_2) {return pret_1.get_pret() < pret_2.get_pret(); });
    return lista;
}

MyList<Produs> ServiceProdus::filtrare_dupa_nume(const std::string& nume) const{
    MyList<Produs> lista_produs = repo_produs.get_all();
    MyList<Produs> filtrat;
    for (const Produs& produs : lista_produs){
        if (produs.get_nume() == nume)
            filtrat.push(produs);
    }
    return filtrat;
}

MyList<Produs> ServiceProdus::filtrare_dupa_producator(const std::string& producator) const{
    MyList<Produs> lista_produs = repo_produs.get_all();
    MyList<Produs> filtrat;
    for (const Produs& produs : lista_produs){
        if (produs.get_producator() == producator)
            filtrat.push(produs);
    }
    return filtrat;
}

MyList<Produs> ServiceProdus::sortare_dupa_nume() const{
    MyList<Produs> lista = repo_produs.get_all();
    std::sort(lista.begin(), lista.end(), [&](const Produs& a, const Produs& b) { return a.get_nume() < b.get_nume(); });
    return lista;
}

MyList<Produs> ServiceProdus::sortare_dupa_nume_si_tip() const{
    MyList<Produs> lista = repo_produs.get_all();
    std::sort(lista.begin(), lista.end(), [](const Produs& a, const Produs& b) {
        if (a.get_nume() == b.get_nume()) return a.get_tip() < b.get_tip();
        return a.get_nume() < b.get_nume();
    });
    return lista;
}
