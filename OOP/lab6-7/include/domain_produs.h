#ifndef DOMAIN_PRODUS_H
#define DOMAIN_PRODUS_H

#include <string>

#include "attribute_produs.h"
#include "produs_tip.h"
class Produs{
    private:
        AttributeProdus attrib;
        ProdusTip tip;
        float pret;

    public:
        Produs() = default;
        Produs(const AttributeProdus& attrib,const ProdusTip tip, const float pret);

        std::string get_nume() const;
        std::string get_producator() const;
        float get_pret() const;
        ProdusTip get_tip() const;

        void set_pret(float pret_nou);
        void set_tip(ProdusTip tip_nou);

        friend std::ostream& operator<<(std::ostream& stream, const Produs& produs);

        bool operator==(const Produs& produs_check) const;

};

#endif
