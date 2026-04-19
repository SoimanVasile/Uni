#ifndef SERVICE_PRODUS_H
#define SERVICE_PRODUS_H

#include <string>
#include "attribute_produs.h"
#include "produs_tip.h"
#include "repo_produs.h"
#include "validator.h"
class ServiceProdus{
    private:
        RepoProdus& repo_produs;
        Validator& validator_produs;

    public:

        ServiceProdus(RepoProdus& repo_produs, Validator& validator);

        void add_produs(const AttributeProdus& attrib, const ProdusTip tip, const float pret);

        MyList<Produs> get_all() const;

        void sterge_produs(const std::string& name, const std::string& producator);

        void modifica_produs(AttributeProdus& attrib, ProdusTip tip, float pret);

        const Produs& find_dupa_nume_si_producator(const std::string& name, const std::string& producator) const;

        MyList<Produs> filtrare_dupa_pret(const float pret) const;
        MyList<Produs> filtrare_dupa_nume(const std::string& nume) const;
        MyList<Produs> filtrare_dupa_producator(const std::string& producator) const;

        MyList<Produs> sortare_dupa_pret() const;
        MyList<Produs> sortare_dupa_nume() const;
        MyList<Produs> sortare_dupa_nume_si_tip() const;
};

#endif
