#include <stdlib.h>
#include <string.h>

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

int sterge_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume){
    int scor[10] = {1,1,1,1,1,1,1,1,1,1};
    int verified = verifica_participant(nume, prenume, scor);

    if (verified != SUCCES) { return verified;}

    return sterge_participant(service_participant->repo_participant,nume, prenume);
}

dto_filtrare* filtrare_dupa_scor(ServiceParticipant *service_participant, int scor_minim){
    dto_filtrare* filtrare = (dto_filtrare*)malloc(sizeof(dto_filtrare));
    filtrare->participanti_filtrati = (Participant**)malloc(service_participant->repo_participant->numar_elemente * sizeof(Participant*));
    filtrare->numar_elemente = 0;
    for (size_t i=0; i<len_repo_participant(service_participant->repo_participant); i++){
        int* scor_participant = get_scor(&service_participant->repo_participant->participanti[i]);
        int good=1;
        for (size_t j=0; j<10; j++){
            if (scor_participant[j]<scor_minim){
                good=0;
            }
        }

        if (good){
            filtrare->participanti_filtrati[filtrare->numar_elemente++] = &service_participant->repo_participant->participanti[i];
        }
    }

    return filtrare;
}

void free_dto_filtrare(dto_filtrare *filtrare){
    free(filtrare->participanti_filtrati);
    free(filtrare);
}

Participant** sorteaza_dupa_nume_participanti(ServiceParticipant *service_participant){

    size_t m = service_participant->repo_participant->numar_elemente;

    if (m == 0){
        return NULL;
    }

    Participant** participanti_sortat = (Participant**)malloc(sizeof(Participant*) * m);

    for (size_t i=0; i<m; i++){
        participanti_sortat[i] = &service_participant->repo_participant->participanti[i];
    }

    int sorted=0;
    while (!sorted){
        sorted = 1;
        for (size_t i=0; i<m-1; i++){
            char* nume1 = get_nume(participanti_sortat[i]);
            char* nume2 = get_nume(participanti_sortat[i+1]);
            if (strcmp(nume1, nume2) > 0){
                Participant* aux = participanti_sortat[i];
                participanti_sortat[i]= participanti_sortat[i+1];
                participanti_sortat[i+1]= aux;
                sorted = 0;
            }
        }
        m--;
    }
    return participanti_sortat;
}

size_t len_service_participanti(ServiceParticipant *service_participanti){
    return len_repo_participant(service_participanti->repo_participant);
}
