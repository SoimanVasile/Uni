#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
    private:
	/* aici e reprezentarea */
	struct Nod {
		TElem elem;
		Nod* urm;
		Nod(TElem e, Nod* urm) : elem(e), urm(urm) {}
	};

	Nod** tabela;
	int m;
	int lungime;
	Relatie rel;

	int d(TCheie c) const {
		return (c < 0 ? -c : c) % m;
	}

    // BC = WC = AC = theta(n)
	void redimensioneaza();
    public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
    // BC = theta(1)
    // WC = O(n)
    // AC = O(n/m)
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
    // BC = theta(1)
    // WC = theta(n)
    // AC = theta(n/m)
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
    // BC = theta(1)
    // WC = O(n)
    // AC = O(n/m)
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
    // BC = WC = AC = theta(1)
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
    // BC = WC = AC = theta(1)
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

};
