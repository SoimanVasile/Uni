#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test_repo.h"
#include "participant.h"
#include "repo_participant.h"
#include "errors.h"

void test_adauga_participant(){
char nume[64] = "Shannon";
char prenume[64] = "Claude";
int scor[10] = {10, 10, 10, 9, 10, 10, 9, 10, 9, 10};
    Participant participant = new_participant(nume, prenume, scor);
    RepoParticipant repo_participant = new_repo_participant();
    adauga_participant(&repo_participant, participant);
    Participant participant1 = repo_participant.participanti[0];

    char* get_nume_participant1 = get_nume(&participant1);
    char* get_prenume_participant1 = get_prenume(&participant1);
    int* get_scor_participant1 = get_scor(&participant1);

    char* get_nume_participant = get_nume(&participant);
    char* get_prenume_participant = get_prenume(&participant);
    int* get_scor_participant = get_scor(&participant);

    for (size_t i=0; i<strlen(get_nume_participant); i++){
        assert(get_nume_participant[i] == get_nume_participant1[i]);
    }

    for (size_t i=0; i<strlen(get_prenume_participant); i++){
        assert(get_prenume_participant[i] == get_prenume_participant1[i]);
    }

    for (size_t i=0; i<10; i++){
        assert(get_scor_participant[i] == get_scor_participant1[i]);
    }

    free_repo_participant(&repo_participant);
}

void test_len_repo_participant(){

char nume[64] = "Shannon";
char prenume[64] = "Claude";
int scor[10] = {10, 10, 10, 9, 10, 10, 9, 10, 9, 10};
    RepoParticipant repo_participant = new_repo_participant();
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));

    assert(len_repo_participant(&repo_participant) == 1);
    free_repo_participant(&repo_participant);
}

void test_schimba_participant() {
    RepoParticipant repo = new_repo_participant();
    int scor1[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int scor2[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    
    Participant p1 = new_participant("Big", "Stein", scor1);
    adauga_participant(&repo, p1);

    // Test successful modification
    Participant p2 = new_participant("Big", "Stein", scor2);
    assert(schimba_participant(&repo, &p2) == SUCCES);
    assert(get_scor(&repo.participanti[0])[0] == 2); // Verificam ca s-a modificat

    // Test modification for non-existent participant
    Participant p_inexistent = new_participant("Alt", "Cineva", scor2);
    assert(schimba_participant(&repo, &p_inexistent) == ERR_NOT_FOUND);

    // Free memory
    free_participant(&p2);
    free_participant(&p_inexistent);
    free_repo_participant(&repo);
}

void test_stergere_participant(){
    RepoParticipant repo_participant = new_repo_participant();

    char* nume = "Dune";
    char* prenume = "Maghiara";
    int scor[10] = {1, 2, 3, 4, 5, 6 ,7 ,8 , 9, 10};

    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    adauga_participant(&repo_participant, new_participant(nume, prenume, scor));
    
    assert(SUCCES == sterge_participant(&repo_participant, nume, prenume));

    assert(len_repo_participant(&repo_participant) == 0);

    char* nume_inexistent = "Open";
    char* prenume_inexistent = "AI";

    sterge_participant(&repo_participant, nume_inexistent, prenume_inexistent);

    assert(len_repo_participant(&repo_participant) == 0);

    free_repo_participant(&repo_participant);
}
