#ifndef UI_H
#define UI_H

#include "service_produs.h"
class UI{
    private:
        ServiceProdus& service_produs;
        void add_produs();
        void print();
        void sterge_produs();
        void modifica_produs();
        void find_dupa_nume_si_producator();
        void filtrare_dupa_pret();
        void filtrare_dupa_nume();
        void filtrare_dupa_producator();
        void sortare_dupa_pret();
        void sortare_dupa_nume();
        void sortare_dupa_nume_si_tip();

    public:
        UI(ServiceProdus& service_produs);
        void run();
};

#endif
