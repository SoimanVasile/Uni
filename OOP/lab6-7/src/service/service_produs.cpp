#include <algorithm>
#include <exception>
#include <string>

#include "produs_tip.h"
#include "validator.h"
#include "service_produs.h"
#include "attribute_produs.h"
#include "domain_produs.h"
#include "repo_produs.h"
#include "undo.h"

ServiceProdus::ServiceProdus(RepoProdus& repo, Validator& validator) : repo_produs(repo), validator_produs(validator) {}

void ServiceProdus::add_produs(const AttributeProdus& attrib, ProdusTip tip, float pret){
    std::string nume = attrib.get_nume();
    std::string producator = attrib.get_producator();
    validator_produs.validare_produs(nume, producator, tip, pret);

    Produs produs_nou(attrib, tip, pret);

    repo_produs.add_produs(produs_nou);
    undo_actions.push_back(std::make_unique<UndoAdauga>(repo_produs, produs_nou));
}

void ServiceProdus::undo() {
    if (undo_actions.empty()) {
        throw ValidatorException("Nu mai exista operatii pt undo!\n");
    }
    undo_actions.back()->doUndo();
    undo_actions.pop_back();
}

std::vector<Produs> ServiceProdus::get_all() const{
    return repo_produs.get_all();
}

void ServiceProdus::sterge_produs(const std::string& name, const std::string& producator){
    validator_produs.validare_produs(name, producator, CARNE, 2.0);
    Produs p_sters = repo_produs.find_dupa_nume_si_producator(name, producator);
    repo_produs.sterge_produs(name, producator);
    undo_actions.push_back(std::make_unique<UndoSterge>(repo_produs, p_sters));
}

void ServiceProdus::modifica_produs(AttributeProdus& attrib, ProdusTip tip, float pret){
    std::string nume = attrib.get_nume();
    std::string producator = attrib.get_producator();
    validator_produs.validare_produs(nume, producator, tip, pret);

    Produs p_vechi = repo_produs.find_dupa_nume_si_producator(nume, producator);
    Produs produs_nou(attrib, tip, pret);

    repo_produs.modifica_produs(produs_nou);
    undo_actions.push_back(std::make_unique<UndoModifica>(repo_produs, p_vechi));
}

const Produs& ServiceProdus::find_dupa_nume_si_producator(const std::string& name, const std::string& producator) const{
    validator_produs.validare_produs(name, producator, CARNE, 2.0);

    return repo_produs.find_dupa_nume_si_producator(name, producator);
}

std::vector<Produs> ServiceProdus::filtrare_dupa_pret(const float pret) const{
    const auto& lista_produs = repo_produs.get_all();
    std::vector<Produs> filtrat;

    for (const Produs& produs : lista_produs){
        if (produs.get_pret() < pret)
            filtrat.push_back(produs);
    }
    return filtrat;
}

std::vector<Produs> ServiceProdus::sortare_dupa_pret() const{
    std::vector<Produs> lista = repo_produs.get_all();
    std::sort(lista.begin(), lista.end(), [](const Produs& pret_1, const Produs& pret_2) {return pret_1.get_pret() < pret_2.get_pret(); });
    return lista;
}

std::vector<Produs> ServiceProdus::filtrare_dupa_nume(const std::string& nume) const{
    const auto& lista_produs = repo_produs.get_all();
    std::vector<Produs> filtrat;
    for (const Produs& produs : lista_produs){
        if (produs.get_nume() == nume)
            filtrat.push_back(produs);
    }
    return filtrat;
}

std::vector<Produs> ServiceProdus::filtrare_dupa_producator(const std::string& producator) const{
    const auto& lista_produs = repo_produs.get_all();
    std::vector<Produs> filtrat;
    for (const Produs& produs : lista_produs){
        if (produs.get_producator() == producator)
            filtrat.push_back(produs);
    }
    return filtrat;
}

std::vector<Produs> ServiceProdus::sortare_dupa_nume() const{
    std::vector<Produs> lista = repo_produs.get_all();
    std::sort(lista.begin(), lista.end(), [&](const Produs& a, const Produs& b) { return a.get_nume() < b.get_nume(); });
    return lista;
}

std::vector<Produs> ServiceProdus::sortare_dupa_nume_si_tip() const{
    std::vector<Produs> lista = repo_produs.get_all();
    std::sort(lista.begin(), lista.end(), [](const Produs& a, const Produs& b) {
        if (a.get_nume() == b.get_nume()) return a.get_tip() < b.get_tip();
        return a.get_nume() < b.get_nume();
    });
    return lista;
}

void ServiceProdus::cos_goleste() {
    cos_cump.goleste();
}

void ServiceProdus::cos_adauga(const std::string& nume) {
    const auto& lista = repo_produs.get_all();
    auto it = std::find_if(lista.begin(), lista.end(), [&nume](const Produs& p) {
        return p.get_nume() == nume;
    });
    if (it != lista.end()) {
        cos_cump.adauga(*it);
        return;
    }
    throw RepoException("Produsul cu numele introdus nu exista!\n");
}

void ServiceProdus::cos_genereaza(size_t numar) {
    cos_cump.genereaza_random(numar, repo_produs.get_all());
}

void ServiceProdus::cos_export_csv(const std::string& filename) const {
    cos_cump.export_csv(filename);
}

void ServiceProdus::cos_export_html(const std::string& filename) const {
    cos_cump.export_html(filename);
}

float ServiceProdus::cos_total() const {
    return cos_cump.get_total();
}

const std::vector<Produs>& ServiceProdus::cos_get_all() const {
    return cos_cump.get_all();
}

// const std::unordered_map<ProdusTip, int> ServiceProdus::count_tips() const {
    // const auto& list = this->repo_produs.get_all();
    // std::unordered_map<ProdusTip, int>
    // for ()
// }
