#include <cassert>
#include "repo_produs.h"
#include "undo.h"

void test_repo() {
    RepoProdus repo;
    assert(repo.size() == 0);
    AttributeProdus a1("n1", "p1");
    Produs p1(a1, CARNE, 10);
    repo.add_produs(p1);
    assert(repo.size() == 1);

    try {
        repo.add_produs(p1);
        assert(false);
    } catch(RepoException& e) {
        assert(e.get_mesaj() == "Acest produs exista deja!\n");
    }

    AttributeProdus a2("n2", "p2");
    Produs p2(a2, LACTATE, 20);
    repo.add_produs(p2);

    assert(repo.find_dupa_index(0) == p1);
    try { repo.find_dupa_index(5); assert(false); } catch(RepoException&) {}

    assert(repo.find_dupa_nume_si_producator("n1", "p1") == p1);
    try { repo.find_dupa_nume_si_producator("n3", "p3"); assert(false); } catch(RepoException&) {}

    Produs p1_mod(a1, LACTATE, 15);
    repo.modifica_produs(p1_mod);
    assert(repo.find_dupa_nume_si_producator("n1", "p1").get_pret() == 15);
    
    AttributeProdus a3("n3", "p3");
    Produs p3(a3, LACTATE, 15);
    try { repo.modifica_produs(p3); assert(false); } catch(RepoException&) {}

    repo.sterge_produs("n1", "p1");
    assert(repo.size() == 1);
    try { repo.sterge_produs("nx", "px"); assert(false); } catch(RepoException&) {}

    auto all = repo.get_all();
    assert(all.size() == 1);
}
