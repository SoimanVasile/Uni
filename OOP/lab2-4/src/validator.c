#include <string.h>

#include "validator.h"
#include "errors.h"

int verifica_participant(char *nume, char *prenume, int *scor){
    if (strlen(nume) == 0) return ERR_INVALID_NUME;
    if (strlen(prenume) == 0) return ERR_INVALID_PRENUME;
    for (int i=0; i<10; i++){
        if (scor[i] <0 || scor[i] >10) return ERR_INVALID_SCOR;
    }

    return SUCCES;
}
