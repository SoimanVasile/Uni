//
// Created by User on 3/17/2026.
//

#include "domain.h"
#include <string.h>
#include <stdlib.h>

MateriePrima* creeaza_materie(char* nume, char* producator, int cantitate) {
    MateriePrima* m = malloc(sizeof(MateriePrima));
    m->nume = strdup(nume);
    m->producator = strdup(producator);
    m->cantitate = cantitate;
    return m;
}

void distruge_materie(MateriePrima* m) {
    free(m->nume);
    free(m->producator);
    free(m);
}

MateriePrima* copiaza_materie(MateriePrima* m) {
    return creeaza_materie(m->nume, m->producator, m->cantitate);
}