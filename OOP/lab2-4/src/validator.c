#include "validator.h"

int verifica_participant(char *nume, char *prenume, int *scor){
    (void) nume;
    (void) prenume;
    for (int i=0; i<10; i++){
        if (scor[i] <0 || scor[i] >10) return 0;
    }

    return 1;
}
