//
// Created by User on 3/17/2026.
//


#ifndef REPO_H
#define REPO_H
#include "domain.h"

typedef struct {
    MateriePrima** elemente;
    int lungime;
    int capacitate;
} Repo;

Repo* creeaza_repo();
void distruge_repo(Repo* r);
int adauga(Repo* r, MateriePrima* m); // Returnează 0 dacă e nou, 1 dacă a existat și s-a făcut update
int sterge(Repo* r, char* nume);
int modifica(Repo* r, char* nume, char* prod_nou, int cant_noua);
MateriePrima* cauta(Repo* r, char* nume);

#endif //LABORATOR_2_4_REPO_H