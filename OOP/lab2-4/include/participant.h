typedef struct{
    char* nume;
    char* prenume;
    int scor[10];
} Participant;

Participant new_participant(char* nume, char* prenume, int scor[]);

void print_participant(Participant* participant);

char* get_nume(Participant* participant);

char* get_prenume(Participant* participant);

char* get_scor(Participant* participant);


