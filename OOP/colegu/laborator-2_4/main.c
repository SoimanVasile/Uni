#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "service.h"

void ruleaza_teste() {

    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);


    assert(adauga_materie(s, "Zahar", "Agrana", 10) == 0);
    assert(r->lungime == 1);


    assert(adauga_materie(s, "Zahar", "Agrana", 5) == 1);
    assert(r->elemente[0]->cantitate == 15);


    assert(adauga_materie(s, "Sare", "Salrom", -5) == -1);


    adauga_materie(s, "Faina", "Baneasa", 20);
    adauga_materie(s, "Lapte", "Zuzu", 50); // Aici se face resize la 4
    assert(r->capacitate == 4);
    assert(r->lungime == 3);


    assert(modifica_materie(s, "Faina", "Dobrogea", 25) == 1);
    assert(strcmp(r->elemente[1]->producator, "Dobrogea") == 0);
    assert(r->elemente[1]->cantitate == 25);


    assert(modifica_materie(s, "Ciocolata", "Milka", 10) == 0);


    assert(sterge_materie(s, "Zahar") == 1);
    assert(r->lungime == 2);
    assert(strcmp(r->elemente[0]->nume, "Faina") == 0);


    assert(sterge_materie(s, "Inexistent") == 0);


    adauga_materie(s, "Apa", "Izvor", 100); // Acum avem: Faina(25), Lapte(50), Apa(100)


    sortare(r, 1, 1);
    assert(strcmp(r->elemente[0]->nume, "Apa") == 0);
    assert(strcmp(r->elemente[2]->nume, "Lapte") == 0);

    //  sortare dupa nume descrescator
    sortare(r, 1, -1);
    assert(strcmp(r->elemente[0]->nume, "Lapte") == 0);

    //  sortare dupa cantitate crescator
    sortare(r, 2, 1);
    assert(r->elemente[0]->cantitate == 25); // Faina

    //  sortare dupa cantitate descrescator
    sortare(r, 2, -1);
    assert(r->elemente[0]->cantitate == 100); // Apa


    int gasit = 0;
    for(int i = 0; i < r->lungime; i ++) {
        if(r->elemente[i]->nume[0] == 'L' && r->elemente[i]->cantitate < 60)
            gasit ++;
    }
    assert(gasit == 1);

    distruge_service(s);
    distruge_repo(r);

    printf("\n>>> TOATE TESTELE AU TRECUT <<<\n");
}

void ui_adauga(Service* s) {
    char n[50], p[50]; int c;
    printf("Nume: "); scanf("%s", n);
    printf("Producator: "); scanf("%s", p);
    printf("Cantitate: "); scanf("%d", &c);
    if (adauga_materie(s, n, p, c) >= 0) printf("Adaugat cu succes!\n");
}

void ui_modifica(Service* s) {
    char nume[50], prod_nou[50];
    int cant_noua;
    printf("Numele materiei de modificat: "); scanf("%s", nume);
    printf("Producator nou: "); scanf("%s", prod_nou);
    printf("Cantitate noua: "); scanf("%d", &cant_noua);

    if (modifica_materie(s, nume, prod_nou, cant_noua))
        printf("Modificare realizata cu succes!\n");
    else
        printf("Materia prima nu a fost gasita.\n");
}

void ui_sterge(Service* s) {
    char nume[50];
    printf("Numele materiei de sters: "); scanf("%s", nume);

    if (sterge_materie(s, nume))
        printf("Sters cu succes!\n");
    else
        printf("Materia prima nu exista.\n");
}

void ui_filtrare(Service* s) {
    char litera;
    int prag;
    printf("Filtrare dupa prima litera: "); scanf(" %c", &litera);
    printf("Si cantitate mai mica de: "); scanf("%d", &prag);

    // Iteram prin repo-ul din service pentru a afisa rezultatele
    int gasit = 0;
    for (int i = 0; i < s->repo->lungime; i ++) {
        MateriePrima* m = s->repo->elemente[i];
        if (m->nume[0] == litera && m->cantitate < prag) {
            printf("%s | %s | %d\n", m->nume, m->producator, m->cantitate);
            gasit = 1;
        }
    }
    if (!gasit)
        printf("Nu exista materii care sa satisfaca criteriile.\n");
}

int main() {

    ruleaza_teste();

    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);

    int opt = -1;

    while (opt != 0) {
            printf("\n==============================");
            printf("\n    --- GESTIUNE COFETARIE ---");
            printf("\n==============================");
            printf("\n 1. Adauga/Actualizeaza materie");
            printf("\n 2. Modifica materie");
            printf("\n 3. Sterge materie");
            printf("\n 4. Filtreaza");
            printf("\n 5. Sorteaza (Nume)");
            printf("\n 0. Iesire");
            printf("\n==============================");
            printf("\n Alegeti optiunea: ");

        if (scanf("%d", &opt) != 1) break;

        switch (opt) {
            case 1:
                ui_adauga(s);
                break;
            case 2:
                ui_modifica(s);
                break;
            case 3:
                ui_sterge(s);
                break;
            case 4:
                ui_filtrare(s);
                break;
            case 5: {
                int ordine;
                printf("Ordine (1-Crescator, -1-Descrecator): "); scanf("%d", &ordine);
                sortare(s->repo, 1, ordine); // 1 pentru sortare dupa nume
                for (int i = 0; i < s->repo->lungime; i++) {
                    printf("%s | %s | %d\n", s->repo->elemente[i]->nume,
                           s->repo->elemente[i]->producator, s->repo->elemente[i]->cantitate);
                }
                break;
            }
            case 0:
                printf("Exit!\n");
                break;
            default:
                printf("Optiune invalida!\n");
        }
    }

    distruge_service(s);
    distruge_repo(r);
    return 0;
}