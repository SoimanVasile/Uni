#pragma once
#include "MyList.h"

typedef struct {
    MyList* list;
} Repo;

Repo* creeaza_repo();
int adauga(Repo* r, TElem m);
int sterge(Repo* r, char* nume);
int modifica(Repo* r, char* nume, char* prod_nou, float cant_noua);
int repo_get_len(Repo *repo);
TElem repo_get_elem_by_index(Repo *repo, int index);
void repo_print(Repo* repo);
void distruge_repo(Repo* r);
