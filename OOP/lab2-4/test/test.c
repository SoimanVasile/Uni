#include "test.h"
#include "test_domeniu.h"
#include "test_repo.h"

void run_all(){
    test_creare_participant();
    test_get_nume();
    test_get_prenume();
    test_get_scor();
    test_adauga_participant();
    test_len_repo_participant();
    printf("Toate testele au rulat cu succes!!");
}
