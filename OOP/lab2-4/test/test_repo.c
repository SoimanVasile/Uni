#include "test_repo.h"
#include "participant.h"
#include "repo_participant.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


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
    Participant participant = new_participant(nume, prenume, scor);
    RepoParticipant repo_participant = new_repo_participant();
    adauga_participant(&repo_participant, participant);
    adauga_participant(&repo_participant, participant);
    adauga_participant(&repo_participant, participant);
    adauga_participant(&repo_participant, participant);
    adauga_participant(&repo_participant, participant);

    assert(len_repo_participant(&repo_participant) == 5);
    free_repo_participant(&repo_participant);
}
