#include <stdlib.h>

#include "participant.h"
#include "repo_participant.h"
#include "equal_overloading.h"
#include "errors.h"

#define REPO_INIT_CAPACITY 2

RepoParticipant new_repo_participant(){
    RepoParticipant repo_participant = {.capacitate = REPO_INIT_CAPACITY, .numar_elemente = 0,.participanti = (Participant*)malloc(REPO_INIT_CAPACITY * sizeof(Participant)) };
    return repo_participant;
}

int adauga_participant(RepoParticipant *repo_participant,Participant participant){
    if (repo_participant->numar_elemente >= repo_participant->capacitate){
        size_t new_capacity = repo_participant->capacitate<<1;

        Participant* temp = realloc(
                repo_participant->participanti,
                new_capacity * sizeof(Participant)
                );

        if (temp == NULL)
            return ERR_MEM_ALLOC;

        repo_participant->participanti = temp;
        repo_participant->capacitate = new_capacity;
    }
    repo_participant->participanti[repo_participant->numar_elemente++] = participant;
    return SUCCES;
}

size_t len_repo_participant(RepoParticipant *repo_participant){
    return repo_participant->numar_elemente;
}

void print_repo_participant(RepoParticipant *repo_participant){
    for (size_t i=0; i<len_repo_participant(repo_participant); i++){
        print_participant(&repo_participant->participanti[i]);
    }
}

void free_repo_participant(RepoParticipant *repo_participant){
    for (size_t i=0; i<repo_participant->numar_elemente; i++){
        free_participant(&repo_participant->participanti[i]);    }
    free(repo_participant->participanti);
}


int schimba_participant(RepoParticipant* repo_participant, Participant* participant){
    for (size_t i=0; i<len_repo_participant(repo_participant); i++){
        if (equal(&repo_participant->participanti[i], participant)) {
            int* scor_vechi = get_scor(&repo_participant->participanti[i]);
            int* scor_nou = get_scor(participant);
            for (size_t i=0; i<10; i++){
                scor_vechi[i] = scor_nou[i];
            }
            return SUCCES;
        }
    }
    return ERR_NOT_FOUND;
}

int sterge_participant(RepoParticipant* repo_participant, char* nume, char* prenume){
    for (size_t i=0; i<len_repo_participant(repo_participant); i++) {
        char* nume_participant = get_nume(&repo_participant->participanti[i]);
        char* prenume_participant = get_prenume(&repo_participant->participanti[i]);
        if (equal(nume_participant, nume) && equal(prenume_participant, prenume)){

        }
    }
}

