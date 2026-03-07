#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "participant.h"

Participant new_participant(char *nume, char *prenume, int *scor){
    Participant participant;

    participant.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(participant.nume, nume);

    participant.prenume = (char*)malloc(strlen(prenume) + 1);
    strcpy(participant.prenume, prenume);

    for (int i=0; i<10; i++)
        participant.scor[i] = scor[i];

    return participant;
}

void print_participant(Participant *participant){
        printf("|Nume: %s| Prenume: %s are scoru: ", participant->nume, participant->prenume);
        for (int i=0; i<10; i++)
            printf("%d ", participant->scor[i]);
        printf("|\n");
}

void free_participant(Participant* participant){
    free(participant->nume);
    free(participant->prenume);
}

char* get_nume(Participant* participant){
    return participant->nume;
}

char* get_prenume(Participant* participant){
    return participant->prenume;
}

int* get_scor(Participant* participant){
    return participant->scor;
}
