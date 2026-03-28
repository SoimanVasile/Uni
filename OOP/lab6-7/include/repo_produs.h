#ifndef REPO_PRODUS_H
#define REPO_PRODUS_H

#include <vector>

#include "domain_produs.h"
class RepoProdus{
    
    private:
        std::vector<Produs> lista_produse;

    public:

        RepoProdus() = default;

        void add_produs(const Produs& produs);

        void print();

        size_t size();
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
