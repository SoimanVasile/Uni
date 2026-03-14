#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
    printf("Citeste nume:");
    getchar();
    fgets(buffer_nume, 64, stdin);
    buffer_nume[strcspn(buffer_nume, "\n")] = '\0';
    printf("Citeste prenume");
    char buffer_prenume[64];
    fgets(buffer_prenume, 64, stdin);
    buffer_prenume[strcspn(buffer_prenume, "\n")] = '\0';
    printf("Citeste 10 scoruri: ");
    int scor[10];
    for (int i=0 ;i<10; i++){
        scanf("%d", &scor[i]);
    }
    
    if (adauga_participant_service(ui->service_participant, buffer_nume, buffer_prenume, scor) != SUCCES) {printf("Nu am reusit sa adaug participantul!\n"); return;};

    printf("Am adaugat cu succes participantul!\n");
}

void modifica_participant_ui(UI *ui){
    char buffer_nume[64];
    printf("Citeste nume:");
    getchar();
    fgets(buffer_nume, 64, stdin);
    buffer_nume[strcspn(buffer_nume, "\n")] = '\0';
    printf("Citeste prenume");
    char buffer_prenume[64];
    fgets(buffer_prenume, 64, stdin);
    buffer_prenume[strcspn(buffer_prenume, "\n")] = '\0';
    printf("Citeste 10 scoruri: ");
    int scor[10];
    for (int i=0 ;i<10; i++){
        scanf("%d", &scor[i]);
    }

    if (modifica_participant_service(ui->service_participant, buffer_nume, buffer_prenume, scor) != SUCCES) {printf("Nu am putut modifica participantul!\n"); return;};

    printf("Am modificat cu succes participantul!\n");

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
        }
    }

    free_repo_participant(&repo_participant);
}
