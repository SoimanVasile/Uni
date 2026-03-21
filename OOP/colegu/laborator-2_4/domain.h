#ifndef DOMAIN_H
#define DOMAIN_H

typedef struct {
    char* nume;
    char* producator;
    float cantitate;
} MateriePrima;

MateriePrima* creeaza_materie(char* nume, char* producator, int cantitate);
void distruge_materie(MateriePrima* m);
MateriePrima* copiaza_materie(MateriePrima* m);

#endif //LABORATOR_2_4_DOMAIN_H