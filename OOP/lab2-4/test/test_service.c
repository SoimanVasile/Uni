#include "service_participant.h"
#include <assert.h>

#include "errors.h"

void test_service_adauga() {
    RepoParticipant repo = new_repo_participant();
    ServiceParticipant srv = new_service_participant(&repo);
    
    int scor_valid[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    int scor_invalid[10] = {-1, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    // Test add valid
    assert(adauga_participant_service(&srv, "Vasile", "Soiman", scor_valid) == SUCCES); // 0 = succes la tine in repo
    assert(len_repo_participant(srv.repo_participant) == 1);

    // Test add invalid (validator respinge)
    assert(adauga_participant_service(&srv, "Vasile", "Soiman", scor_invalid) == ERR_INVALID_SCOR); // atentie: la tine return 0 inseamna eroare in service
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
