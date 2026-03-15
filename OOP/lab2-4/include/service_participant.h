#ifndef PARTICIPANT_SERVICE_H
#define PARTICIPANT_SERVICE_H

#include "participant.h"
#include "repo_participant.h"
typedef struct {
    RepoParticipant* repo_participant;
} ServiceParticipant;

ServiceParticipant new_service_participant(RepoParticipant* repo_participant);

/*
 *@brief verifica daca datele inserate sunt bine si adauga participant in service
 *@param service_participant: pointer la ServicePaticipant
 *@param nume: string
 *@param prenume: string
 *@param scor: vector de int de 10 elemente
 *@return SUCCES daca a reusit sa puna participantul
 */
int adauga_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume, int* scor);

void print_service_participant(ServiceParticipant* service_participant);

int modifica_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume, int* scor);

int sterge_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume);


typedef struct {
    Participant** participanti_filtrati;
    int numar_elemente;
} dto_filtrare;

dto_filtrare* filtrare_dupa_scor(ServiceParticipant* service_participant, int scor_minim);

void free_dto_filtrare(dto_filtrare* filtrare);

Participant** sorteaza_dupa_nume_participanti(ServiceParticipant* service_participant);

size_t len_service_participanti(ServiceParticipant* service_participanti);
#endif
