#include "participant.h"
#include "repo_participant.h"
#include "service_participant.h"
#include "validator.h"
#include "errors.h"

ServiceParticipant new_service_participant(RepoParticipant* repo_participant){
    ServiceParticipant service_participant = {.repo_participant = repo_participant};
    return service_participant;
}


int adauga_participant_service(ServiceParticipant *service_participant, char *nume, char *prenume, int *scor){
    int verified = verifica_participant(nume, prenume, scor);
    if (verified != SUCCES) {return verified;}

    Participant participant = new_participant(nume, prenume, scor);

    return adauga_participant(service_participant->repo_participant, participant);
}

void print_service_participant(ServiceParticipant* service_participant){
    print_repo_participant(service_participant->repo_participant);
}

int modifica_participant_service(ServiceParticipant *service_participant, char *nume, char *prenume, int *scor){
    int verified = verifica_participant(nume, prenume, scor);
    if (verified != SUCCES){ return verified;}

    Participant participant = new_participant(nume, prenume, scor);

    int result = schimba_participant(service_participant->repo_participant, &participant);

    free_participant(&participant);

    return result;
}
