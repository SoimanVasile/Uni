#pragma once
#include "repo.h"
#include "domain.h"
typedef struct {
    Repo* repo;
    MyList* undoStack; 
} Service;

Service* creeaza_service(Repo* r);
int adauga_materie(Service* s, char* nume, char* prod, float cant);
int sterge_materie(Service* s, char* nume);
int modifica_materie(Service* s, char* nume, char* prod, float cant);
void sortare(Service* service, int criteriu, int ordine);
int undo(Service* s);
void distruge_service(Service* s);
MateriePrima** filtreaza_materii(Service* s, char litera, float prag, int* lungime_rezultat);
void service_print(Service* service);
