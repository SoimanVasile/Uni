#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	rel = r;
	m = 10;
	lungime = 0;
	tabela = new Nod*[m];
	for (int i = 0; i < m; ++i) {
		tabela[i] = nullptr;
	}
}

void MDO::redimensioneaza() {
	int m_nou = m * 2;
	Nod** tabela_noua = new Nod*[m_nou];
	for (int i = 0; i < m_nou; ++i) {
		tabela_noua[i] = nullptr;
	}
	for (int i = 0; i < m; ++i) {
		Nod* curent = tabela[i];
		while (curent != nullptr) {
			Nod* urmator = curent->urm;
			int poz = (curent->elem.first < 0 ? -curent->elem.first : curent->elem.first) % m_nou;
			
			if (tabela_noua[poz] == nullptr || rel(curent->elem.first, tabela_noua[poz]->elem.first)) {
				curent->urm = tabela_noua[poz];
				tabela_noua[poz] = curent;
			} else {
				Nod* temp = tabela_noua[poz];
				while (temp->urm != nullptr && !rel(curent->elem.first, temp->urm->elem.first)) {
				    temp = temp->urm;
                }
				curent->urm = temp->urm;
				temp->urm = curent;
			}
			
			curent = urmator;
		}
	}
	delete[] tabela;
	tabela = tabela_noua;
	m = m_nou;
}

void MDO::adauga(TCheie c, TValoare v) {
	if (lungime >= m) {
		redimensioneaza();
	}
	int poz = d(c);
	Nod* nod_nou = new Nod(TElem(c, v), nullptr);
	
	if (tabela[poz] == nullptr || rel(c, tabela[poz]->elem.first)) {
		nod_nou->urm = tabela[poz];
		tabela[poz] = nod_nou;
	} else {
		Nod* curent = tabela[poz];
		while (curent->urm != nullptr && !rel(c, curent->urm->elem.first)) {
			curent = curent->urm;
		}
		nod_nou->urm = curent->urm;
		curent->urm = nod_nou;
	}
	lungime++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> rez;
	int poz = d(c);
	Nod* curent = tabela[poz];
	while (curent != nullptr) {
		if (curent->elem.first == c) {
			rez.push_back(curent->elem.second);
		}
		curent = curent->urm;
	}
	return rez;
}

bool MDO::sterge(TCheie c, TValoare v) {
	int poz = d(c);
	Nod* curent = tabela[poz];
	Nod* prec = nullptr;
	while (curent != nullptr) {
		if (curent->elem.first == c && curent->elem.second == v) {
			if (prec == nullptr) {
				tabela[poz] = curent->urm;
			} else {
				prec->urm = curent->urm;
			}
			delete curent;
			lungime--;
			return true;
		}
		prec = curent;
		curent = curent->urm;
	}
	return false;
}

int MDO::dim() const {
	return lungime;
}

bool MDO::vid() const {
	return lungime == 0;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	for (int i = 0; i < m; ++i) {
		Nod* curent = tabela[i];
		while (curent != nullptr) {
			Nod* de_sters = curent;
			curent = curent->urm;
			delete de_sters;
		}
	}
	delete[] tabela;
}
