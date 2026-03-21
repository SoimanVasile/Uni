#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "participant.h"
#include "repo_participant.h"
#include "service_participant.h"
#include "ui.h"
#include "errors.h"

UI new_ui(ServiceParticipant* service_participant){
    UI ui = {.service_participant = service_participant};
    return ui;
}

void adauga_participant_ui(UI* ui){
    char buffer_nume[64];
    printf("Citeste nume: ");
    getchar();
    fgets(buffer_nume, 64, stdin);
    buffer_nume[strcspn(buffer_nume, "\n")] = '\0';
    printf("Citeste prenume: ");
    char buffer_prenume[64];
    fgets(buffer_prenume, 64, stdin);
    buffer_prenume[strcspn(buffer_prenume, "\n")] = '\0';
    printf("Citeste 10 scoruri: ");
    int scor[10];
    for (int i=0 ;i<10; i++){
        scanf("%d", &scor[i]);
    }
    int result = adauga_participant_service(ui->service_participant, buffer_nume, buffer_prenume, scor);
    
    switch (result){
        case ERR_INVALID_NUME: {printf("Nume invalid!\n"); break;}
        case ERR_INVALID_PRENUME: {printf("Prenume invalid!\n"); break;}
        case ERR_INVALID_SCOR: {printf("Scor invalid!\n"); break;}
        case ERR_MEM_ALLOC: {printf("Nu am putut alocare memorie!\n"); break;}
        case ERR_PAR_ALREADY_EXISTS: {printf("Participantul exista deja!\n"); break;}
        case SUCCES: {printf("Am adaugat cu succes participantul!\n"); break;}
    }

}

void modifica_participant_ui(UI *ui){
    char buffer_nume[64];
    printf("Citeste nume: ");
    getchar();
    fgets(buffer_nume, 64, stdin);
    buffer_nume[strcspn(buffer_nume, "\n")] = '\0';
    printf("Citeste prenume: ");
    char buffer_prenume[64];
    fgets(buffer_prenume, 64, stdin);
    buffer_prenume[strcspn(buffer_prenume, "\n")] = '\0';
    printf("Citeste 10 scoruri: ");
    int scor[10];
    for (int i=0 ;i<10; i++){
        scanf("%d", &scor[i]);
    }
    
    int result = modifica_participant_service(ui->service_participant, buffer_nume, buffer_prenume, scor);

    switch (result){
        case ERR_INVALID_NUME: {printf("Nume invalid!\n"); break;}
        case ERR_INVALID_PRENUME: {printf("Prenume invalid!\n"); break;}
        case ERR_INVALID_SCOR: {printf("Scor invalid!"); break;}
        case ERR_MEM_ALLOC: {printf("Nu am putut alocare memorie!\n"); break;}
        case ERR_NOT_FOUND: {printf("Nu am putut modifica participantul!\n"); break;}
        case SUCCES: {printf("Am modificat cu succes participantul!\n"); break;}
    }

}
void sterge_participant_ui(UI* ui){
    char buffer_nume[64];
    printf("Citeste nume: ");
    getchar();
    fgets(buffer_nume, 64, stdin);
    buffer_nume[strcspn(buffer_nume, "\n")] = '\0';
    printf("Citeste prenume: ");
    char buffer_prenume[64];
    fgets(buffer_prenume, 64, stdin);
    buffer_prenume[strcspn(buffer_prenume, "\n")] = '\0';

    int result = sterge_participant_service(ui->service_participant, buffer_nume, buffer_prenume);

    switch (result){
        case ERR_INVALID_NUME: {printf("Nume invalid!\n"); break;}
        case ERR_INVALID_PRENUME: {printf("Prenume invalid!\n"); break;}
        case ERR_INVALID_SCOR: {printf("Scor invalid!\n"); break;}
        case ERR_MEM_ALLOC: {printf("Nu am putut alocare memorie!\n"); break;}
        case ERR_NOT_FOUND: {printf("Participantul nu exista!\n"); break;}
        case SUCCES: {printf("Am sters cu succes participantul!\n"); break;}
    }
}

void filtrare_dupa_scor_ui(UI* ui){
    int scor;
    printf("Citeste scor minim: ");
    scanf("%d", &scor);

    dto_filtrare* filtrare = filtrare_dupa_scor(ui->service_participant, scor);

    for (int i=0; i<filtrare->numar_elemente; i++){
        print_participant(filtrare->participanti_filtrati[i]);
    }

    free_dto_filtrare(filtrare);
}

void sorteaza_participanti_ui(UI* ui){
    Participant** sortat = sorteaza_dupa_nume_participanti(ui->service_participant);
    size_t size = len_service_participanti(ui->service_participant);

    for (size_t i=0; i<size; i++)
        print_participant(sortat[i]);

    free(sortat);
}

void print_participant_ui(UI* ui){
    print_service_participant(ui->service_participant);
}

void menu() {
    FILE *fp = fopen("menu.txt", "r");
    if (fp == NULL) {
        printf("Failed to open the file\n");
        return;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }

    fclose(fp);
}
void run(){
    RepoParticipant repo_participant = new_repo_participant();
    ServiceParticipant service_participant = new_service_participant(&repo_participant);
    UI ui = new_ui(&service_participant);
    int exit=0;
    while(!exit){
        menu();
        int user_mode;
        printf("Alege un mod: ");
        scanf("%d", &user_mode);
        switch (user_mode){
            case 0: {exit=1; break;}
            case 1: {adauga_participant_ui(&ui); break;}
            case 2: {print_participant_ui(&ui); break;}
            case 3: {modifica_participant_ui(&ui); break;}
            case 4: {sterge_participant_ui(&ui); break;}
            case 5: {filtrare_dupa_scor_ui(&ui); break;}
            case 6: {sorteaza_participanti_ui(&ui); break;}
        }
    }

    free_repo_participant(&repo_participant);
}
