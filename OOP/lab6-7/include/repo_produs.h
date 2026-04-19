#ifndef REPO_PRODUS_H
#define REPO_PRODUS_H

#include "MyList.h"
#include "domain_produs.h"
class RepoProdus{
    
    private:
        MyList<Produs> lista_produse;

    public:

        RepoProdus() = default;

        void add_produs(const Produs& produs);

        size_t size() const;

        void sterge_produs(const std::string& nume, const std::string& producator);

        void modifica_produs(const Produs& produs);

        const Produs& find_dupa_index(size_t i) const;

        const Produs& find_dupa_nume_si_producator(const std::string& nume, const std::string& producator) const;

        const MyList<Produs>& get_all() const;
};

#include <string>

class RepoException {
private:
    std::string mesaj_eroare;
public:
    RepoException(std::string mesaj) : mesaj_eroare(mesaj) {}
    
    std::string get_mesaj() const { return mesaj_eroare; }
};

#endif
