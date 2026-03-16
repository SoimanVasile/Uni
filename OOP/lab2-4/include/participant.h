#ifndef PARTICIPANT_H
#define PARTICIPANT_H

typedef struct{
    char* nume;
    char* prenume;
    int scor[10];
} Participant;

/**
 * @brief Creeaza un nou participant. Aloca memorie pentru nume si prenume.
 * @param nume String ce reprezinta numele participantului.
 * @param prenume String ce reprezinta prenumele participantului.
 * @param scor Array de 10 intregi reprezentand scorurile participantului (1-10).
 * @return Structura Participant initializata cu datele primite.
 */
Participant new_participant(char* nume, char* prenume, int scor[]);

/**
 * @brief Printeaza detaliile unui participant la consola.
 * @param participant Pointer la participantul ce trebuie printat.
 */
void print_participant(Participant* participant);

/**
 * @brief Returneaza numele participantului.
 * @param participant Pointer la participant.
 * @return String reprezentand numele participantului.
 */
char* get_nume(Participant* participant);

/**
 * @brief Returneaza prenumele participantului.
 * @param participant Pointer la participant.
 * @return String reprezentand prenumele participantului.
 */
char* get_prenume(Participant* participant);

/**
 * @brief Returneaza scorurile participantului.
 * @param participant Pointer la participant.
 * @return Pointer catre array-ul de 10 intregi reprezentand scorurile.
 */
int* get_scor(Participant* participant);

/**
 * @brief Elibereaza memoria alocata dinamic pentru un participant (nume si prenume).
 * @param participant Pointer la participantul ce trebuie eliberat.
 */
void free_participant(Participant* participant);

/**
 * @brief Modifica numele participantului si gestioneaza eliberarea/alocarea memoriei.
 * @param participant Pointer la participant.
 * @param nume Noul nume al participantului.
 */
void set_nume(Participant* participant, char* nume);

/**
 * @brief Modifica prenumele participantului si gestioneaza eliberarea/alocarea memoriei.
 * @param participant Pointer la participant.
 * @param prenume Noul prenume al participantului.
 */
void set_prenume(Participant* participant, char* prenume);

#endif
