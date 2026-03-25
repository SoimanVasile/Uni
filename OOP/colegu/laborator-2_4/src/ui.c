#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "domain.h"
#include "service.h"


void print_domain(MateriePrima *m){
    printf(" Nume: %s | Producator: %s | cantitate: %f ", m->nume, m->producator, m->cantitate);
}

void repo_print(Repo *repo){
    for (int i=0; i<my_list_get_len(repo->list); i++){
        print_domain(my_list_get_elem_by_index(repo->list, i));
        printf("\n");
    }
}

void service_print(Service *service){
    repo_print(service->repo);
}

void ui_adauga(Service* s) {
    char n[50], p[50]; 
    float c; 
    printf("Nume: "); scanf("%49s", n);
    printf("Producator: "); scanf("%49s", p);
    printf("Cantitate: "); scanf("%f", &c); 
    
    if (adauga_materie(s, n, p, c) >= 0) 
        printf("Adaugat cu succes!\n");
    else 
        printf("Eroare: Cantitatea nu poate fi negativa!\n");
}

void ui_modifica(Service* s) {
    char nume[50], prod_nou[50];
    float cant_noua; 
    printf("Numele materiei de modificat: "); scanf("%49s", nume);
    printf("Producator nou: "); scanf("%49s", prod_nou);
    printf("Cantitate noua: "); scanf("%f", &cant_noua); 
    
    if (modifica_materie(s, nume, prod_nou, cant_noua)) 
        printf("Modificat cu succes!\n");
    else 
        printf("Eroare: Materia prima nu exista.\n");
}

void ui_print(Service* s){
    service_print(s);
}

void ui_sterge(Service* s) {
    char nume[50];
    printf("Numele materiei de sters: "); scanf("%49s", nume);
    
    if (sterge_materie(s, nume)) 
        printf("Sters cu succes!\n");
    else 
        printf("Eroare: Materia prima nu exista.\n");
}

void ui_filtrare(Service* s) {
    char litera;
    float prag; 
    printf("Filtrare dupa prima litera: "); scanf(" %c", &litera);
    printf("Si cantitate mai mica de: "); scanf("%f", &prag); 

    int lungime_rezultat = 0;
    // Cerem de la Service lista filtrata
    MateriePrima** rezultat = filtreaza_materii(s, litera, prag, &lungime_rezultat);

    if (lungime_rezultat == 0) {
        printf("Nu exista materii care sa satisfaca criteriile.\n");
    } else {
        printf("\n--- Rezultate Filtrare ---\n");
        for (int i = 0; i < lungime_rezultat; i++) {
            printf("%s | %s | %.2f\n", rezultat[i]->nume, rezultat[i]->producator, rezultat[i]->cantitate);
        }
    }
    
    // Eliberam array-ul returnat de service (NU si elementele din el)
    free(rezultat); 
}

void ui_sortare(Service* s){

    int ordine, criteriu;
    printf("Criteriu (1-Nume, 2-Cantitate): "); scanf("%d", &criteriu);
    printf("Ordine (1-Crescator, -1-Descrecator): "); scanf("%d", &ordine);
    sortare(s, criteriu, ordine);
                
    printf("\n--- Inventar Sortat ---\n");
    for (int i = 0; i < repo_get_len(s->repo); i++) {
        MateriePrima* m = (MateriePrima*)repo_get_elem_by_index(s->repo, i);
        printf("%s | %s | %.2f\n", m->nume, m->producator, m->cantitate);
    }
}

void run_ui(Service* s) {
    int opt = -1;

    while (opt != 0) {
        printf("\n==============================");
        printf("\n    --- GESTIUNE COFETARIE ---");
        printf("\n==============================");
        printf("\n 1. Adauga materie");
        printf("\n 2. Modifica materie");
        printf("\n 3. Sterge materie");
        printf("\n 4. Filtreaza"); 
        printf("\n 5. Sorteaza");
        printf("\n 6. Undo");
        printf("\n 0. Iesire");
        printf("\n==============================");
        printf("\n Alegeti optiunea: ");

        if (scanf("%d", &opt) != 1) break;

        switch (opt) {
            case 1: ui_adauga(s); break;
            case 2: ui_modifica(s); break;
            case 3: ui_sterge(s); break;
            case 4: ui_filtrare(s); break;
            case 5: {
                ui_sortare(s);
                break;
            }
            case 6: {
                if (undo(s)) printf("Undo realizat cu succes!\n");
                else printf("Nu se mai poate face undo! Istoricul este gol.\n");
                break;
            }
            case 7: {
                ui_print(s); break;
                    }
            case 0: printf("Exit!\n"); break;
            default: printf("Optiune invalida!\n");
        }
    }
}
