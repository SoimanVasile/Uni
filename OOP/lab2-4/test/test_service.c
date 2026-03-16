#include "service_participant.h"
#include "test_service.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

void test_service_adauga() {
    RepoParticipant repo = new_repo_participant();
    ServiceParticipant srv = new_service_participant(&repo);
    
    int scor_valid[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    int scor_invalid[10] = {-1, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    // Test add valid
    assert(adauga_participant_service(&srv, "Vasile", "Soiman", scor_valid) == SUCCES);
    assert(len_repo_participant(srv.repo_participant) == 1);

    // Test add invalid (validator respinge)
    assert(adauga_participant_service(&srv, "Vasile", "Soiman", scor_invalid) == ERR_INVALID_SCOR);
    assert(len_repo_participant(srv.repo_participant) == 1); // lungimea ramane 1
    
    free_repo_participant(&repo);
}

void test_service_modifica() {
    RepoParticipant repo = new_repo_participant();
    ServiceParticipant srv = new_service_participant(&repo);
    
    int scor1[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    int scor2[10] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};

    adauga_participant_service(&srv, "Vasile", "Soiman", scor1);
    
    // Test modifica cu succes
    assert(modifica_participant_service(&srv, "Vasile", "Soiman", scor2) == SUCCES); 
    assert(get_scor(&srv.repo_participant->participanti[0])[0] == 9);

    free_repo_participant(&repo);
}

void test_service_sterge() {
    RepoParticipant repo = new_repo_participant();
    ServiceParticipant srv = new_service_participant(&repo);
    
    int scor[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    adauga_participant_service(&srv, "Vasile", "Soiman", scor);
    assert(len_service_participanti(&srv) == 1);
    
    // Test stergere succes
    assert(sterge_participant_service(&srv, "Vasile", "Soiman") == SUCCES);
    assert(len_service_participanti(&srv) == 0);

    // Test stergere inexistent
    assert(sterge_participant_service(&srv, "Vasile", "Soiman") != SUCCES);

    free_repo_participant(&repo);
}

void test_service_filtrare() {
    RepoParticipant repo = new_repo_participant();
    ServiceParticipant srv = new_service_participant(&repo);
    
    int scor_bun[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10}; // Average: 10
    int scor_slab[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};          // Average: 5

    adauga_participant_service(&srv, "Eminescu", "Mihai", scor_bun);
    adauga_participant_service(&srv, "Creanga", "Ion", scor_slab);

    dto_filtrare* rezultat = filtrare_dupa_scor(&srv, 9);
    
    assert(rezultat->numar_elemente == 1);
    // Asigura-te ca l-a gasit pe cel cu scor_bun
    
    free_dto_filtrare(rezultat);
    free_repo_participant(&repo);
}

void test_len_service() {
    RepoParticipant repo = new_repo_participant();
    ServiceParticipant srv = new_service_participant(&repo);
    
    assert(len_service_participanti(&srv) == 0);
    int scor[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    adauga_participant_service(&srv, "A", "B", scor);
    assert(len_service_participanti(&srv) == 1);

    free_repo_participant(&repo);
}

void test_service_sortare() {
    RepoParticipant repo = new_repo_participant();
    ServiceParticipant srv = new_service_participant(&repo);
    
    int scor[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    // Adaugam participanti in ordine nealfabetica
    adauga_participant_service(&srv, "Zebra", "Ana", scor);
    adauga_participant_service(&srv, "Badea", "Ion", scor);
    adauga_participant_service(&srv, "Avram", "Vasile", scor);

    // Sortam
    Participant** participanti_sortati = sorteaza_dupa_nume_participanti(&srv);

    // Verificam daca sunt ordonati corect (Avram -> Badea -> Zebra)
    assert(strcmp(get_nume(participanti_sortati[0]), "Avram") == 0);
    assert(strcmp(get_nume(participanti_sortati[1]), "Badea") == 0);
    assert(strcmp(get_nume(participanti_sortati[2]), "Zebra") == 0);

    // Eliberam memoria alocata pentru array-ul de pointeri returnat de functia de sortare
    // (Presupunand ca functia intoarce un array de pointeri alocat dinamic)
    free(participanti_sortati); 
    free_repo_participant(&repo);
}
