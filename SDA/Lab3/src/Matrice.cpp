#include "../include/Matrice.h"
#include <algorithm>
#include <exception>

using namespace std;

Matrice::Matrice(int m, int n) {	/* de adaugat */
    if (m<=0 || n<=0){
        throw std::exception();
    }
    this->numar_coloane = n;
    this->numar_linii = m;
    this->Linii.resize(numar_linii+1, 0);
}  

int Matrice::nrLinii() const{	/* de adaugat */
    return this->numar_linii;
}

int Matrice::nrColoane() const{	/* de adaugat */
	return this->numar_coloane;
}

TElem Matrice::element(int i, int j) const{	/* de adaugat */
    if (i>=this->numar_linii || j>=this->numar_coloane || i<0 || j<0){
        throw std::exception();
    }

    int z=this->Linii[i];
    while (z<Linii[i+1] && this->Coloana[z] < j){
        z++;
    }
    if (z < this->Linii[i+1] && this->Coloana[z] == j) return this->valoare[z];

	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) {

    if (i>=this->numar_linii || j>=this->numar_coloane || i<0 || j<0){
        throw std::exception();
    }

    int z = this->Linii[i];

    while (z < this->Linii[i+1] && this->Coloana[z]<j){
        z++;
    }
    int valoare_veche;

    if (z<this->Linii[i+1] && this->Coloana[z] == j){
        if (e == NULL_TELEMENT){
            valoare_veche = this->valoare[z];
            this->valoare.erase(this->valoare.begin() + z);
            this->Coloana.erase(this->Coloana.begin() + z);
            for (int k=i+1; k<=this->numar_linii; k++){
                this->Linii[k]--;
            }
        }
        else{
            valoare_veche = this->valoare[z];
            this->valoare[z] = e;
        }

        return valoare_veche;
    }

    if (e != NULL_TELEMENT){
        this->valoare.insert(this->valoare.begin() + z, e);
        this->Coloana.insert(this->Coloana.begin() + z, j);
        for (int k=i+1; k<=this->numar_linii; k++){
            this->Linii[k]++;
        }
    }

	return NULL_TELEMENT;
}

