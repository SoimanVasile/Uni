#ifndef REPO_PARTICIPANT_H
#define REPO_PARTICIPANT_H
#include "participant.h"
#include <stdio.h>

typedef struct {
    size_t capacitate;
    size_t numar_elemente;
    Participant* participanti;
} RepoParticipant;

/**
 * @brief Initializeaza un nou repository de participanti cu o capacitate predefinita.
 * @return O structura RepoParticipant goala.
 */
RepoParticipant new_repo_participant();

/**
 * @brief Adauga un participant in repository. Redimensioneaza vectorul daca capacitatea este depasita.
 * @param repo_participant Pointer la repository.
 * @param participant Structura Participant de adaugat.
 * @return O valoare intreaga reprezentand statusul operatiei (ex: SUCCES).
 */
int adauga_participant(RepoParticipant* repo_participant, Participant participant);

/**
 * @brief Printeaza toti participantii din repository la consola.
 * @param repo_participant Pointer la repository.
 */
void print_repo_participant(RepoParticipant* repo_participant);

/**
 * @brief Returneaza numarul de participanti din repository.
 * @param repo_participant Pointer la repository.
 * @return Numarul de elemente.
 */
size_t len_repo_participant(RepoParticipant *repo_participant);

/**
 * @brief Elibereaza toata memoria alocata pentru repository si participantii din el.
 * @param repo_participant Pointer la repository.
 */
void free_repo_participant(RepoParticipant *repo_participant);

/**
 * @brief Cauta un participant dupa nume si prenume si ii actualizeaza datele cu cele ale noului participant.
 * @param repo_participant Pointer la repository.
 * @param participant Pointer la noul participant ale carui date vor inlocui pe cele vechi.
 * @return SUCCES daca inlocuirea a reusit, sau ERR_NOT_FOUND daca participantul nu a fost gasit.
 */
int schimba_participant(RepoParticipant* repo_participant, Participant* participant);

/**
 * @brief Sterge un participant din repository identificat prin nume si prenume.
 * @param repo_participant Pointer la repository.
 * @param nume Numele participantului de sters.
 * @param prenume Prenumele participantului de sters.
 * @return SUCCES daca a fost sters, sau ERR_NOT_FOUND daca participantul nu a fost gasit.
 */
int sterge_participant(RepoParticipant* repo_participant, char* nume, char* prenume);

#endif
