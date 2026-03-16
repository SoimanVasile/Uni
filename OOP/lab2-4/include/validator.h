#ifndef VALIDATOR_H
#define VALIDATOR_H

/**
 * @brief Verifica daca datele unui participant sunt corecte conform cerintelor.
 * @param nume Numele participantului ce trebuie evaluat (nu poate fi gol).
 * @param prenume Prenumele participantului ce trebuie evaluat (nu poate fi gol).
 * @param scor Vectorul de scoruri (10 elemente, cu valori cuprinse intre 1 si 10).
 * @return SUCCES daca datele sunt valide, altfel un cod de eroare (ex: ERR_INVALID_SCOR).
 */
int verifica_participant(char* nume, char* prenume, int* scor);

#endif
