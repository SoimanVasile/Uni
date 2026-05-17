#include "Iterator.h"
#include "DO.h"

#include <exception>
using namespace std;

void DO::iniSpatiuLiber(int capacitate) {
    for (int i = 0; i < capacitate - 1; i++) {
        urm[i] = i + 1;
    }
    urm[capacitate - 1] = -1;
    primLiber = 0;
}

int DO::aloca() {
    int i = primLiber;
    if (i != -1) {
        primLiber = urm[primLiber];
    }
    return i;
}

void DO::dealoca(int i) {
    urm[i] = primLiber;
    primLiber = i;
}

void DO::redim() {
    int cp_nou = cp * 2;
    TElem* e_nou = new TElem[cp_nou];
    int* urm_nou = new int[cp_nou];

    for (int i = 0; i < cp; i++) {
        e_nou[i] = e[i];
        urm_nou[i] = urm[i];
    }

    for (int i = cp; i < cp_nou - 1; i++) {
        urm_nou[i] = i + 1;
    }
    urm_nou[cp_nou - 1] = -1;
    primLiber = cp;
    cp = cp_nou;

    delete[] e;
    delete[] urm;
    
    e = e_nou;
    urm = urm_nou;
}

int DO::creeazaNod(TCheie c, TValoare v) {
    if (primLiber == -1) {
        redim();
    }
    int i = aloca();
    e[i] = make_pair(c, v);
    urm[i] = -1;
    return i;
}

DO::DO(Relatie r) {
    this->r = r;
    cp = 10;
    e = new TElem[cp];
    urm = new int[cp];
    prim = -1;
    iniSpatiuLiber(cp);
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
    int curent = prim;
    int prev = -1;

    while (curent != -1) {
        if (e[curent].first == c) {
            TValoare old = e[curent].second;
            e[curent].second = v;
            return old;
        }
        if (!r(e[curent].first, c)) {
            break;
        }
        prev = curent;
        curent = urm[curent];
    }

    int nou = creeazaNod(c, v);
    if (prev == -1) {
        urm[nou] = prim;
        prim = nou;
    } else {
        urm[nou] = urm[prev];
       urm[prev] = nou;
    }
    return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
    int curent = prim;
    while (curent != -1) {
        if (e[curent].first == c) {
            return e[curent].second;
        }
        curent = urm[curent];
    }
    return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
    int curent = prim;
    int prev = -1;

    while (curent != -1) {
        if (e[curent].first == c) {
            if (prev == -1) {
                prim = urm[curent];
            } else {
                urm[prev] = urm[curent];
            }
            TValoare old = e[curent].second;
            dealoca(curent);
            return old;
        }
        prev = curent;
        curent = urm[curent];
    }
    return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
    int count = 0;
    int curent = prim;
    while (curent != -1) {
        count++;
        curent = urm[curent];
    }
    return count;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
    return prim == -1;
}

Iterator DO::iterator() const {
	return Iterator(*this);
}

DO::~DO() {
    delete[] e;
    delete[] urm;
}
