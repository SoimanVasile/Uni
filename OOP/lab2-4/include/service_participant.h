#ifndef PARTICIPANT_SERVICE_H
#define PARTICIPANT_SERVICE_H

#include "participant.h"
#include "repo_participant.h"
typedef struct {
    RepoParticipant* repo_participant;
} ServiceParticipant;

ServiceParticipant new_service_participant(RepoParticipant* repo_participant);

int adauga_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume, int* scor);

#endif
