#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "repo_participant.h"
#include "service_participant.h"
#include "ui.h"

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
    
    adauga_participant_service(ui->service_participant, buffer_nume, buffer_prenume, scor);
}

void print_participant_ui(UI* ui){
    print_service_participant(ui->service_participant);
}

void menu(){
  int fd = open("menu.txt", O_RDONLY);

  if (fd <0){
    printf ("Failed to open the file");
    return;
  }
  
  int rd = 0;
  char buffer[200];
  while ((rd = read(fd, buffer, 200))){
    buffer[rd] = '\0';
    printf("%s\n", buffer);
  }
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
        }
    }

    free_repo_participant(&repo_participant);
}
