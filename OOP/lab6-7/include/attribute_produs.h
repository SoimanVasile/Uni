#ifndef ATTRIBUTE_PRODUS_H
#define ATTRIBUTE_PRODUS_H

#include <string>
#include "produs_tip.h"
class AttributeProdus{
    private:
        std::string nume, producator;
        ProdusTip tip;
        float pret;

    public:
        AttributeProdus(std::string n, std::string prod, ProdusTip t, float p);

        std::string get_nume() const;
        std::string get_producator() const;
        ProdusTip get_tip() const;
        float get_pret() const;

        void set_nume(std::string& nume);
        void set_producator(std::string& producator);
        void set_tip(ProdusTip tip_nou);
        void set_pret(float pret_nou);
};

#endif
