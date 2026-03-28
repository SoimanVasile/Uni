#ifndef DOMAIN_PRODUS_H
#define DOMAIN_PRODUS_H

#include <string>

#include "attribute_produs.h"
#include "produs_tip.h"
class Produs{
    private:
        AttributeProdus attrib;

    public:
        Produs(AttributeProdus& attrib);

        std::string get_nume() const;
        std::string get_producator() const;
        float get_pret() const;
        ProdusTip get_tip() const;

        void set_nume(std::string& nume);
        void set_producator(std::string& producator_nou);
        void set_pret(float pret_nou);
        void set_tip(ProdusTip tip_nou);

        friend std::ostream& operator<<(std::ostream& stream, const Produs& produs);

};

#endif
