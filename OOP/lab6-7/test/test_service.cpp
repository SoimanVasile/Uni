#include <cassert>
#include "service_produs.h"
#include "validator.h"
#include "undo.h"
#include <fstream>

void test_export_cos() {
    RepoProdus repo;
    Validator val;
    ServiceProdus srv(repo, val);

    srv.add_produs(AttributeProdus("prod1", "prod"), CARNE, 10);
    srv.cos_adauga("prod1");

    srv.cos_export_csv("test_export.csv");
    srv.cos_export_html("test_export.html");

    std::ifstream in_csv("test_export.csv");
    assert(in_csv.is_open());
    in_csv.close();

    std::ifstream in_html("test_export.html");
    assert(in_html.is_open());
    in_html.close();

    try {
        srv.cos_export_csv("/invalid_path/test_export.csv");
        assert(false);
    } catch(RepoException&) {}

    try {
        srv.cos_export_html("/invalid_path/test_export.html");
        assert(false);
    } catch(RepoException&) {}
}

void test_service() {
    RepoProdus repo;
    Validator val;
    ServiceProdus srv(repo, val);

    AttributeProdus a1("a", "p1");
    AttributeProdus a2("b", "p1");
    AttributeProdus a3("a", "p2");

    srv.add_produs(a2, CARNE, 10);
    srv.add_produs(a1, LACTATE, 20);
    srv.add_produs(a3, CURATENIE, 5);

    assert(srv.get_all().size() == 3);

    srv.modifica_produs(a1, DULCIURI, 25);
    assert(srv.find_dupa_nume_si_producator("a", "p1").get_pret() == 25);

    auto f_pret = srv.filtrare_dupa_pret(15);
    assert(f_pret.size() == 2); // 10 and 5

    auto f_nume = srv.filtrare_dupa_nume("a");
    assert(f_nume.size() == 2); // a/p1, a/p2

    auto f_prod = srv.filtrare_dupa_producator("p1");
    assert(f_prod.size() == 2); // a/p1, b/p1

    auto s_pret = srv.sortare_dupa_pret();
    assert(s_pret[0].get_pret() == 5);
    assert(s_pret[1].get_pret() == 10);
    assert(s_pret[2].get_pret() == 25);

    auto s_nume = srv.sortare_dupa_nume();
    assert(s_nume[0].get_nume() == "a");
    assert(s_nume[1].get_nume() == "a");
    assert(s_nume[2].get_nume() == "b");

    auto s_nt = srv.sortare_dupa_nume_si_tip();
    assert(s_nt[0].get_nume() == "a" && s_nt[0].get_tip() == DULCIURI);
    assert(s_nt[1].get_nume() == "a" && s_nt[1].get_tip() == CURATENIE);

    srv.sterge_produs("a", "p1");
    assert(srv.get_all().size() == 2);

    RepoProdus frepo;
    ServiceProdus fsrv(frepo, val);

    AttributeProdus fa("test1", "p");
    fsrv.add_produs(fa, CARNE, 100);
    fsrv.undo();
    assert(fsrv.get_all().size() == 0);

    fsrv.add_produs(fa, CARNE, 100);
    fsrv.modifica_produs(fa, DULCIURI, 200);
    fsrv.undo();
    assert(fsrv.get_all().at(0).get_tip() == CARNE);
    
    fsrv.sterge_produs("test1", "p");
    fsrv.undo();
    assert(fsrv.get_all().size() == 1);
    fsrv.undo();
    try {
        fsrv.undo(); 
        assert(false);
    } catch(ValidatorException&) {}

    fsrv.add_produs(fa, CARNE, 100);
    fsrv.cos_adauga("test1");
    try { 
        fsrv.cos_adauga("inexistent"); 
        assert(false);
    } catch(RepoException&) {}
    assert(fsrv.cos_get_all().size() == 1);
    assert(fsrv.cos_total() == 100);

    fsrv.cos_goleste();
    assert(fsrv.cos_get_all().size() == 0);

    fsrv.add_produs(AttributeProdus("test2", "p"), LACTATE, 50);
    fsrv.cos_genereaza(5);
    assert(fsrv.cos_get_all().size() == 5);

    test_export_cos();
}
