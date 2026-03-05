#include <stdio.h>
#include "participant.h"

Participant new_participant(char *nume, char *prenume, int *scor){
    Participant participant;
    participant.nume = nume;
    participant.prenume = prenume;
    for (int i=0; i<10; i++)
        participant.scor[i] = scor[i];
    return participant;
}

void print_participant(Participant *participant){
        printf("%s %s are scoru: ", participant->nume, participant->prenume);
        for (int i=0; i<10; i++)
            printf("%d ", participant->scor[i]);
}
