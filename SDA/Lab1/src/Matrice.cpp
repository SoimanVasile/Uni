#include "../include/Matrice.h"
#include <exception>

using namespace std;

// BC = WC = AC: Theta(m)
Matrice::Matrice(int m, int n) : Linii(m + 1), Coloana(10), valoare(10) {
    if (m <= 0 || n <= 0) {
        throw std::exception();
    }
    this->numar_coloane = n;
    this->numar_linii = m;
    this->Linii.manual_resize(m + 1, 0);
}

// BC = WC = AC: Theta(1)
int Matrice::nrLinii() const {
    return this->numar_linii;
}

// BC = WC = AC: Theta(1)
int Matrice::nrColoane() const {
    return this->numar_coloane;
}

// BC: Theta(1), WC: Theta(ki), AC: Theta(ki), unde ki = numarul de elemente non-zero pe linia i
TElem Matrice::element(int i, int j) const {
    if (i >= this->numar_linii || j >= this->numar_coloane || i < 0 || j < 0) {
        throw std::exception();
    }

    int z = this->Linii[i];
    while (z < Linii[i + 1] && this->Coloana[z] < j) {
        z++;
    }
    
    if (z < this->Linii[i + 1] && this->Coloana[z] == j) {
        return this->valoare[z];
    }

    return NULL_TELEMENT;
}

// BC: Theta(1)
// WC: Theta(ki + k + m), unde ki = numarul de elemente non-zero pe linia i, k = numar total de elemente non-zero, m = numar de linii
// AC: Theta(ki + k + m)
//   - ki pt cautarea liniara pe linia i
//   - k pt insert/stergere
//   - m pt actualizarea lui Linii
TElem Matrice::modifica(int i, int j, TElem e) {
    if (i >= this->numar_linii || j >= this->numar_coloane || i < 0 || j < 0) {
        throw std::exception();
    }

    int z = this->Linii[i];
    while (z < this->Linii[i + 1] && this->Coloana[z] < j) {
        z++;
    }

    TElem valoare_veche;

    if (z < this->Linii[i + 1] && this->Coloana[z] == j) {
        valoare_veche = this->valoare[z];
        if (e == NULL_TELEMENT) {
            this->valoare.erase(z);
            this->Coloana.erase(z);
            for (int k = i + 1; k <= this->numar_linii; k++) {
                this->Linii[k]--;
            }
        } else {
            this->valoare[z] = e;
        }
        return valoare_veche;
    }

    if (e != NULL_TELEMENT) {
        this->valoare.insert(z, e);
        this->Coloana.insert(z, j);
        for (int k = i + 1; k <= this->numar_linii; k++) {
            this->Linii[k]++;
        }
    }

    return NULL_TELEMENT;
}
