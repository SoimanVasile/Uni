#ifndef UI_H
#define UI_H

#include "service_produs.h"
class UI{
    private:
        ServiceProdus& service_produs;
        void add_produs();
        void print();

    public:
        UI(ServiceProdus& service_produs);
        void run();
};

#endif
