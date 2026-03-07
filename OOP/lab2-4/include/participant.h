#ifndef PARTICIPANT_H
#define PARTICIPANT_H

typedef struct{
    char* nume;
    char* prenume;
    int scor[10];
} Participant;

Participant new_participant(char* nume, char* prenume, int scor[]);

void print_participant(Participant* participant);

char* get_nume(Participant* participant);

char* get_prenume(Participant* participant);

int* get_scor(Participant* participant);

void free_participant(Participant* participant);

#endif
