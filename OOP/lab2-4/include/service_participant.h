#ifndef PARTICIPANT_SERVICE_H
#define PARTICIPANT_SERVICE_H

#include "participant.h"
#include "repo_participant.h"

typedef struct {
    RepoParticipant* repo_participant;
} ServiceParticipant;

/**
 * @brief Initializeaza un service ce opereaza pe un repository dat.
 * @param repo_participant Pointer catre un RepoParticipant.
 * @return O structura ServiceParticipant.
 */
ServiceParticipant new_service_participant(RepoParticipant* repo_participant);

/**
 * @brief Valideaza datele si adauga participantul in repository prin intermediul service-ului.
 * @param service_participant Pointer la ServiceParticipant.
 * @param nume String reprezentand numele.
 * @param prenume String reprezentand prenumele.
 * @param scor Vector de 10 scoruri (int).
 * @return SUCCES daca operatia reuseste, altfel cod de eroare (ex: validare esuata).
 */
int adauga_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume, int* scor);

/**
 * @brief Printeaza toti participantii existenti prin intermediul service-ului.
 * @param service_participant Pointer la ServiceParticipant.
 */
void print_service_participant(ServiceParticipant* service_participant);

/**
 * @brief Valideaza datele si modifica un participant existent pe baza numelui si prenumelui.
 * @param service_participant Pointer la ServiceParticipant.
 * @param nume Numele curent (string).
 * @param prenume Prenumele curent (string).
 * @param scor Noul vector de scoruri.
 * @return SUCCES daca a fost modificat, altfel cod de eroare.
 */
int modifica_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume, int* scor);

/**
 * @brief Sterge un participant din repository pe baza de nume si prenume.
 * @param service_participant Pointer la ServiceParticipant.
 * @param nume Numele participantului de sters.
 * @param prenume Prenumele participantului de sters.
 * @return SUCCES daca a fost sters, altfel cod de eroare (ex: ERR_NOT_FOUND).
 */
int sterge_participant_service(ServiceParticipant* service_participant, char* nume, char* prenume);

typedef struct {
    Participant** participanti_filtrati;
    int numar_elemente;
} dto_filtrare;

/**
 * @brief Returneaza o lista filtrata de participanti care au un anumit scor.
 * @param service_participant Pointer la ServiceParticipant.
 * @param scor_minim Scorul de referinta pentru filtrare.
 * @return O structura dto_filtrare care contine elementele filtrata alocate dinamic.
 */
dto_filtrare* filtrare_dupa_scor(ServiceParticipant* service_participant, int scor_minim);

/**
 * @brief Elibereaza memoria alocata pentru o structura DTO de filtrare.
 * @param filtrare Pointer catre dto_filtrare ce trebuie eliberata.
 */
void free_dto_filtrare(dto_filtrare* filtrare);

/**
 * @brief Returneaza o lista cu toti participantii sortata alfabetic dupa nume/prenume.
 * @param service_participant Pointer la ServiceParticipant.
 * @return Pointer la un array de pointeri Participant** (copie) care sunt ordonati.
 */
Participant** sorteaza_dupa_nume_participanti(ServiceParticipant* service_participant);

/**
 * @brief Returneaza numarul de participanti direct prin service.
 * @param service_participanti Pointer la ServiceParticipant.
 * @return Numarul elementelor stocate in repository-ul referentiat.
 */
size_t len_service_participanti(ServiceParticipant* service_participanti);

#endif
