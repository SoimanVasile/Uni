#include <cassert>
#include <sstream>
#include "attribute_produs.h"
#include "domain_produs.h"
#include "produs_tip.h"

void test_domain() {
    AttributeProdus attr("lapte", "napolact");
    assert(attr.get_nume() == "lapte");
    assert(attr.get_producator() == "napolact");

    Produs p(attr, LACTATE, 5.5);
    assert(p.get_nume() == "lapte");
    assert(p.get_producator() == "napolact");
    assert(p.get_tip() == LACTATE);
    assert(p.get_pret() == 5.5);

    p.set_pret(6.0);
    p.set_tip(CARNE);
    assert(p.get_pret() == 6.0);
    assert(p.get_tip() == CARNE);

    AttributeProdus attr2("lapte", "napolact");
    Produs p2(attr2, LACTATE, 5.5);
    assert(p == p2);

    AttributeProdus attr3("paine", "vel");
    Produs p3(attr3, CARNE, 5.5);
    assert(!(p == p3));

    std::stringstream ss;
    ss << p3;
    assert(ss.str() == "| Nume: paine | Producator: vel | Tip: CARNE | Pret: 5.5 |\n");
}

void test_produs_tip() {
    std::stringstream ss;
    ss << LACTATE << " " << CARNE << " " << DULCIURI << " " << CURATENIE;
    assert(ss.str() == "LACTATE CARNE DULCIURI CURATENIE");

    ProdusTip t;
    std::stringstream sin("lactate Carne dulciuri CURATENIE ceva_gresit");
    sin >> t; assert(t == LACTATE);
    sin >> t; assert(t == CARNE);
    sin >> t; assert(t == DULCIURI);
    sin >> t; assert(t == CURATENIE);
    try {
        sin >> t;
        assert(false);
    } catch(ProdusTipExpection& e) {
        assert(e.mesaj() == "Nu exista acest tip!\n");
    }
}
