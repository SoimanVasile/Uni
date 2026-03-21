//
// Created by User on 3/17/2026.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "repo.h"

typedef struct {
    Repo* repo;
} Service;

Service* creeaza_service(Repo* r);
void distruge_service(Service* s);

int adauga_materie(Service* s, char* nume, char* prod, int cant);
int sterge_materie(Service* s, char* nume);
int modifica_materie(Service* s, char* nume, char* prod, int cant);

// returneaza o copie pt repo filtrat sau sortat
Repo* filtrare(Service* s, char litera, int cantitate_max);
void sortare(Repo* r, int criteriu, int ordine);

#endif //LABORATOR_2_4_SERVICE_H