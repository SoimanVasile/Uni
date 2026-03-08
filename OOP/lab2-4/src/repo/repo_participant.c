#include <stdlib.h>

#include "participant.h"
#include "repo_participant.h"
#include "equal_overloading.h"

#define REPO_INIT_CAPACITY 256

RepoParticipant new_repo_participant(){
    RepoParticipant repo_participant = {.capacitate = REPO_INIT_CAPACITY, .numar_elemente = 0,.participanti = (Participant*)malloc(REPO_INIT_CAPACITY * sizeof(Participant)) };
    return repo_participant;
}

int adauga_participant(RepoParticipant *repo_participant,Participant participant){
    if (repo_participant->numar_elemente >= repo_participant->capacitate)
        return 1;

    repo_participant->participanti[repo_participant->numar_elemente++] = participant;
    return 0;
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
            return 1;
        }
    }
    return 0;
}

