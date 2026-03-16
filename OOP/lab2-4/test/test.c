#include "test.h"
#include "test_domeniu.h"
#include "test_repo.h"
#include "test_service.h"
#include "test_validator.h"
#include <stdio.h>

void run_all(){
    test_creare_participant();
    test_get_nume();
    test_get_prenume();
    test_get_scor();
    test_setters();

    test_adauga_participant();
    test_len_repo_participant();
    test_schimba_participant();
    test_stergere_participant();

    test_validator();

    test_service_adauga();
    test_service_modifica();
    test_service_sterge();
    test_service_filtrare();
    test_len_service();
    test_service_sortare();

    printf("Toate testele au rulat cu succes!!\n");
}
