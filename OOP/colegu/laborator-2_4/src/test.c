#include "test.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void test_domain() {
    MateriePrima* m = creeaza_materie("Zahar", "Agrana", 10.5);
    assert(strcmp(m->nume, "Zahar") == 0);
    assert(strcmp(m->producator, "Agrana") == 0);
    assert(m->cantitate == 10.5);

    MateriePrima* copie = copiaza_materie(m);
    assert(strcmp(copie->nume, "Zahar") == 0);
    assert(copie->cantitate == 10.5);

    distruge_materie(m);
    distruge_materie(copie);
}

void test_repo() {
    Repo* r = creeaza_repo();
    assert(repo_get_len(r) == 0);

    // Test Adaugare
    MateriePrima* m1 = creeaza_materie("Zahar", "Agrana", 10.0);
    assert(adauga(r, m1) == 0);
    assert(repo_get_len(r) == 1);

    // Test Adaugare duplicat (Merge cantitate)
    MateriePrima* m2 = creeaza_materie("Zahar", "Agrana", 5.0);
    assert(adauga(r, m2) == 1);
    assert(((MateriePrima*)repo_get_elem_by_index(r, 0))->cantitate == 15.0);

    // Test Modificare
    assert(modifica(r, "Zahar", "Margaritar", 20.0) == 1);
    assert(strcmp(((MateriePrima*)repo_get_elem_by_index(r, 0))->producator, "Margaritar") == 0);
    assert(modifica(r, "Inexistent", "Nimic", 0) == 0);

    // Test Stergere element care NU e ultimul (forteaza shift-ul in lista)
    MateriePrima* m3 = creeaza_materie("Faina", "Baneasa", 30.0);
    adauga(r, m3);
    assert(repo_get_len(r) == 2);
    assert(sterge(r, "Zahar") == 1);
    assert(repo_get_len(r) == 1);
    assert(strcmp(((MateriePrima*)repo_get_elem_by_index(r, 0))->nume, "Faina") == 0);

    // Test Stergere element inexistent
    assert(sterge(r, "Inexistent") == 0);

    // Stergere ultimul element
    assert(sterge(r, "Faina") == 1);
    assert(repo_get_len(r) == 0);

    distruge_repo(r);
}

void test_service() {
    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);

    // Test Adaugare Validari
    assert(adauga_materie(s, "Faina", "Baneasa", 20.0) == 0);
    assert(adauga_materie(s, "Lapte", "Zuzu", 50.0) == 0);
    assert(adauga_materie(s, "Sare", "Salrom", -5.0) == -1);
    assert(repo_get_len(r) == 2);

    // Test Modificare / Stergere
    assert(modifica_materie(s, "Faina", "Dobrogea", 25.0) == 1);
    assert(modifica_materie(s, "Ciocolata", "Milka", 10.0) == 0);
    assert(sterge_materie(s, "Lapte") == 1);
    assert(repo_get_len(r) == 1);

    // Test Sortare
    adauga_materie(s, "Apa", "Izvor", 100.0);
    adauga_materie(s, "Zahar", "Agrana", 10.0);
    
    sortare(s, 1, 1);
    assert(strcmp(((MateriePrima*)repo_get_elem_by_index(r, 0))->nume, "Apa") == 0);
    
    sortare(s, 2, -1);
    assert(((MateriePrima*)repo_get_elem_by_index(r, 0))->cantitate == 100.0);

    distruge_service(s);
    distruge_repo(r);
}

void test_undo() {
    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);

    assert(undo(s) == 0);

    // Adaugam 2 elemente
    adauga_materie(s, "Faina", "Baneasa", 20.0);
    adauga_materie(s, "Lapte", "Zuzu", 50.0);
    assert(repo_get_len(r) == 2);

    // Undo la a doua adaugare
    assert(undo(s) == 1);
    assert(repo_get_len(r) == 1);
    assert(strcmp(((MateriePrima*)repo_get_elem_by_index(r, 0))->nume, "Faina") == 0);

    // Modificam
    modifica_materie(s, "Faina", "Dobrogea", 25.0);
    assert(((MateriePrima*)repo_get_elem_by_index(r, 0))->cantitate == 25.0);

    // Undo la modificare
    assert(undo(s) == 1);
    assert(((MateriePrima*)repo_get_elem_by_index(r, 0))->cantitate == 20.0);

    // Stergem
    sterge_materie(s, "Faina");
    assert(repo_get_len(r) == 0);

    // Undo la stergere
    assert(undo(s) == 1);
    assert(repo_get_len(r) == 1);

    distruge_service(s);
    distruge_repo(r);
}

void test_filtreaza() {
    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);

    adauga_materie(s, "Faina", "Baneasa", 20.0);
    adauga_materie(s, "Fulgi", "Nestle", 5.0);
    adauga_materie(s, "Lapte", "Zuzu", 3.0);
    adauga_materie(s, "Apa", "Izvorul", 100.0);

    int lungime = 0;
    // Filtreaza dupa litera 'F' si prag 25.0
    MateriePrima** rezultat = filtreaza_materii(s, 'F', 25.0, &lungime);
    assert(lungime == 2);
    free(rezultat);

    // Filtreaza dupa litera 'L' si prag 10.0
    rezultat = filtreaza_materii(s, 'L', 10.0, &lungime);
    assert(lungime == 1);
    assert(strcmp(rezultat[0]->nume, "Lapte") == 0);
    free(rezultat);

    // Filtreaza fara rezultate
    rezultat = filtreaza_materii(s, 'Z', 1.0, &lungime);
    assert(lungime == 0);
    free(rezultat);

    // Filtreaza: litera se potriveste dar cantitatea >= prag (branch coverage)
    rezultat = filtreaza_materii(s, 'F', 5.0, &lungime);
    assert(lungime == 0);
    free(rezultat);

    distruge_service(s);
    distruge_repo(r);
}

void test_service_sterge_inexistent() {
    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);

    adauga_materie(s, "Faina", "Baneasa", 20.0);
    // Stergerea unui element inexistent trebuie sa returneze 0
    assert(sterge_materie(s, "Inexistent") == 0);
    assert(repo_get_len(r) == 1);

    distruge_service(s);
    distruge_repo(r);
}

void test_service_adauga_duplicat() {
    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);

    assert(adauga_materie(s, "Faina", "Baneasa", 20.0) == 0);
    // Adaugare duplicat - se face merge
    assert(adauga_materie(s, "Faina", "Baneasa", 10.0) == 1);
    assert(repo_get_len(r) == 1);
    assert(((MateriePrima*)repo_get_elem_by_index(r, 0))->cantitate == 30.0);

    distruge_service(s);
    distruge_repo(r);
}

void test_sortare_cantitate_crescator() {
    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);

    adauga_materie(s, "Zahar", "Agrana", 50.0);
    adauga_materie(s, "Faina", "Baneasa", 10.0);
    adauga_materie(s, "Lapte", "Zuzu", 30.0);

    sortare(s, 2, 1); // Cantitate, crescator
    assert(((MateriePrima*)repo_get_elem_by_index(r, 0))->cantitate == 10.0);
    assert(((MateriePrima*)repo_get_elem_by_index(r, 1))->cantitate == 30.0);
    assert(((MateriePrima*)repo_get_elem_by_index(r, 2))->cantitate == 50.0);

    sortare(s, 1, -1); // Nume, descrescator
    assert(strcmp(((MateriePrima*)repo_get_elem_by_index(r, 0))->nume, "Zahar") == 0);

    distruge_service(s);
    distruge_repo(r);
}

void test_my_list() {
    // Test my_list_pop pe lista goala
    MyList* list = my_list_create((DestroyFunction)distruge_materie);
    assert(my_list_pop(list) == NULL);
    my_list_distruge(list);
}

void ruleaza_toate_testele() {
    printf("Rulez testele...\n");
    test_domain();
    test_repo();
    test_service();
    test_undo();
    test_filtreaza();
    test_service_sterge_inexistent();
    test_service_adauga_duplicat();
    test_sortare_cantitate_crescator();
    test_my_list();
    printf(">>> TOATE TESTELE AU TRECUT <<<\n");
}
