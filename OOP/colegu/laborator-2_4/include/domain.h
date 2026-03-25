#pragma once

typedef struct {
    char* nume;
    char* producator;
    float cantitate; // Schimbat in float
} MateriePrima;

MateriePrima* creeaza_materie(char* nume, char* producator, float cantitate);
void distruge_materie(MateriePrima* m);
MateriePrima* copiaza_materie(MateriePrima* m);
void print_domain(MateriePrima* m);
