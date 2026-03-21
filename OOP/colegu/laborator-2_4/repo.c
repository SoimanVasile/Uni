//
// Created by User on 3/17/2026.
//

#include "repo.h"
#include <stdlib.h>
#include <string.h>

Repo* creeaza_repo() {
    Repo* r = malloc(sizeof(Repo));
    r->lungime = 0;
    r->capacitate = 2;
    r->elemente = malloc(r->capacitate * sizeof(MateriePrima*));
    return r;
}

void asigura_capacitate(Repo* r) {
    if (r->lungime < r->capacitate) return;
    r->capacitate *= 2;
    r->elemente = realloc(r->elemente, r->capacitate * sizeof(MateriePrima*));
}

int adauga(Repo* r, MateriePrima* m) {
    for (int i = 0; i < r->lungime; i++) {
        if (strcmp(r->elemente[i]->nume, m->nume) == 0) {
            r->elemente[i]->cantitate += m->cantitate;
            distruge_materie(m); // Nu mai avem nevoie de copia nouă
            return 1;
        }
    }
    asigura_capacitate(r);
    r->elemente[r->lungime++] = m;
    return 0;
}

int sterge(Repo* r, char* nume) {
    int index = -1;
    for (int i = 0; i < r->lungime; i++) {
        if (strcmp(r->elemente[i]->nume, nume) == 0) { index = i; break; }
    }
    if (index == -1) return 0;
    distruge_materie(r->elemente[index]);
    for (int i = index; i < r->lungime - 1; i++) r->elemente[i] = r->elemente[i+1];
    r->lungime--;
    return 1;
}

int modifica(Repo* r, char* nume, char* prod_nou, int cant_noua) {
    for (int i = 0; i < r->lungime; i++) {
        if (strcmp(r->elemente[i]->nume, nume) == 0) {
            free(r->elemente[i]->producator);
            r->elemente[i]->producator = strdup(prod_nou);
            r->elemente[i]->cantitate = cant_noua;
            return 1;
        }
    }
    return 0;
}

void distruge_repo(Repo* r) {
    for (int i = 0; i < r->lungime; i++) distruge_materie(r->elemente[i]);
    free(r->elemente);
    free(r);
}