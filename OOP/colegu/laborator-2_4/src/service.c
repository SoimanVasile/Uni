#include "service.h"
#include "domain.h"
#include "repo.h"
#include <stdlib.h>
#include <string.h>

void distruge_undo_state(TElem state) {
    my_list_distruge((MyList*)state);
}

Service* creeaza_service(Repo* r) {
    Service* s = malloc(sizeof(Service));
    s->repo = r;
    s->undoStack = my_list_create(distruge_undo_state);
    return s;
}

int adauga_materie(Service* s, char* nume, char* prod, float cant) {
    if (cant < 0) return -1;
    
    MyList* to_save = my_list_copy(s->repo->list, (CopyFunction)copiaza_materie);
    
    MateriePrima* m = creeaza_materie(nume, prod, cant);
    int res = adauga(s->repo, m);
    
    my_list_add_element(s->undoStack, to_save);
    
    return res;
}

int sterge_materie(Service* s, char* nume) {
    MyList* to_save = my_list_copy(s->repo->list, (CopyFunction)copiaza_materie);
    int res = sterge(s->repo, nume);
    
    if (res == 1) my_list_add_element(s->undoStack, to_save);
    else my_list_distruge(to_save);
    
    return res;
}

int modifica_materie(Service* s, char* nume, char* prod, float cant) {
    MyList* to_save = my_list_copy(s->repo->list, (CopyFunction)copiaza_materie);
    int res = modifica(s->repo, nume, prod, cant);
    
    if (res == 1) my_list_add_element(s->undoStack, to_save);
    else my_list_distruge(to_save);
    
    return res;
}

int undo(Service* s) {
    if (my_list_get_len(s->undoStack) == 0) {
        return 0; 
    }
    MyList* previousState = (MyList*)my_list_pop(s->undoStack);
    
    my_list_distruge(s->repo->list);
    
    s->repo->list = previousState;
    return 1;
}

void sortare(Service* service, int criteriu, int ordine) {
    int len = repo_get_len(service->repo);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            int cmp = 0;
            MateriePrima* elem_i = (MateriePrima*)repo_get_elem_by_index(service->repo, i);
            MateriePrima* elem_j = (MateriePrima*)repo_get_elem_by_index(service->repo, j);
            
            if (criteriu == 1) cmp = strcmp(elem_i->nume, elem_j->nume);
            else cmp = (elem_i->cantitate > elem_j->cantitate) - (elem_i->cantitate < elem_j->cantitate);

            if ((ordine == 1 && cmp > 0) || (ordine == -1 && cmp < 0)) {
                my_list_swap(service->repo->list, i, j);
            }
        }
    }
}

void distruge_service(Service* s) {
    my_list_distruge(s->undoStack); 
    free(s);
}

MateriePrima** filtreaza_materii(Service* s, char litera, float prag, int* lungime_rezultat) {
    int len = repo_get_len(s->repo);
    MateriePrima** rezultat = malloc(len * sizeof(MateriePrima*));
    *lungime_rezultat = 0;
    
    for (int i = 0; i < len; i++) {
        MateriePrima* m = (MateriePrima*)repo_get_elem_by_index(s->repo, i);
        if (m->nume[0] == litera && m->cantitate < prag) {
            rezultat[*lungime_rezultat] = m;
            (*lungime_rezultat)++;
        }
    }
    
    return rezultat;
}

