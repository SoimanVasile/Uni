#include "repo.h"
#include "MyList.h"
#include "domain.h"
#include <stdlib.h>
#include <string.h>

Repo* creeaza_repo() {
    Repo* r = malloc(sizeof(Repo));
    r->list = my_list_create((DestroyFunction)distruge_materie); 
    return r;
}

int adauga(Repo* r, TElem m) {
    MateriePrima* materie_noua = (MateriePrima*)m;
    for (int i = 0; i < repo_get_len(r); i++) {
        MateriePrima* existent = (MateriePrima*)repo_get_elem_by_index(r, i);
        if (strcmp(existent->nume, materie_noua->nume) == 0) {
            existent->cantitate += materie_noua->cantitate;
            distruge_materie(materie_noua); 
            return 1; 
        }
    }
    my_list_add_element(r->list, m);
    return 0; 
}

int sterge(Repo* r, char* nume) {
    for (int i = 0; i < repo_get_len(r); i++) {
        MateriePrima* m = (MateriePrima*)repo_get_elem_by_index(r, i);
        if (strcmp(m->nume, nume) == 0) {
            my_list_remove_by_index(r->list, i);
            return 1;
        }
    }
    return 0;
}

int modifica(Repo* r, char* nume, char* prod_nou, float cant_noua) {
    for (int i = 0; i < repo_get_len(r); i++) {
        MateriePrima* m = (MateriePrima*)repo_get_elem_by_index(r, i);
        if (strcmp(m->nume, nume) == 0) {
            MateriePrima* nou = creeaza_materie(nume, prod_nou, cant_noua);
            my_list_set_elem_by_index(r->list, i, nou);
            return 1;
        }
    }
    return 0;
}

int repo_get_len(Repo *repo){
    return my_list_get_len(repo->list);
}

TElem repo_get_elem_by_index(Repo *repo, int index){
    return my_list_get_elem_by_index(repo->list, index);
}

void distruge_repo(Repo* r) {
    my_list_distruge(r->list);
    free(r);
}

