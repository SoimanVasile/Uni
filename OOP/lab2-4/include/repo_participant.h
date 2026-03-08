#ifndef REPO_PARTICIPANT_H
#define REPO_PARTICIPANT_H
#include "participant.h"
#include <stdio.h>

typedef struct {
    size_t capacitate;
    size_t numar_elemente;
    Participant* participanti;
} RepoParticipant;

RepoParticipant new_repo_participant();

int adauga_participant(RepoParticipant* repo_participant, Participant participant);

void print_repo_participant(RepoParticipant* repo_participant);

size_t len_repo_participant(RepoParticipant *repo_participant);

void free_repo_participant(RepoParticipant *repo_participant);

int schimba_participant(RepoParticipant* repo_participant, Participant* participant);

#endif 
