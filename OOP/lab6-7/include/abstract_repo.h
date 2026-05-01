#pragma once

#include "domain_produs.h"
#include <vector>

class AbstractRepo{
    public:
        virtual void add_produs(const Produs& produs)=0;
        virtual size_t size() const=0;
        virtual void sterge_produs(const std::string& nume, const std::string& producator)=0;
        virtual void modifica_produs(const Produs& produs_nou)=0;
        virtual const Produs& find_dupa_index(size_t i) const=0;
        virtual const Produs& find_dupa_nume_si_producator(const std::string& nume, const std::string& producator) const=0;
        virtual const std::vector<Produs>& get_all() const=0;
        virtual ~AbstractRepo()=default;
};
