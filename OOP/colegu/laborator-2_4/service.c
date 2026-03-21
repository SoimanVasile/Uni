#include "service.h"
#include <stdlib.h>
#include <string.h>

//  Creare service
Service* creeaza_service(Repo* r) {
    Service* s = malloc(sizeof(Service));
    s->repo = r;
    return s;
}

//  Adaugare
int adauga_materie(Service* s, char* nume, char* prod, int cant) {
    if (cant < 0) return -1;
    MateriePrima* m = creeaza_materie(nume, prod, cant);
    return adauga(s->repo, m);
}

//  Stergere
int sterge_materie(Service* s, char* nume) {
    return sterge(s->repo, nume);
}

//  Modificare
int modifica_materie(Service* s, char* nume, char* prod, int cant) {
    return modifica(s->repo, nume, prod, cant);
}

//  Sortare
void sortare(Repo* r, int criteriu, int ordine) {
    for (int i = 0; i < r->lungime - 1; i++) {
        for (int j = i + 1; j < r->lungime; j++) {
            int cmp = 0;
            if (criteriu == 1) cmp = strcmp(r->elemente[i]->nume, r->elemente[j]->nume);
            else cmp = (r->elemente[i]->cantitate - r->elemente[j]->cantitate);

            if ((ordine == 1 && cmp > 0) || (ordine == -1 && cmp < 0)) {
                MateriePrima* aux = r->elemente[i];
                r->elemente[i] = r->elemente[j];
                r->elemente[j] = aux;
            }
        }
    }
}


void distruge_service(Service* s) {
    free(s);
}