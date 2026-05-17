#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO {
	friend class Iterator;
    private:
        Relatie r;
		int cp;
		int prim;
		int primLiber;
		TElem* e;
		int* urm;

        //BC=AC=WC=theta(1)
		int aloca();

        //BC=AC=WC=theta(1)
		void dealoca(int i);

        //BC=AC=WC=theta(1) amortizat
		int creeazaNod(TCheie c, TValoare v);

        //BC=AC=WC=theta(n)
		void iniSpatiuLiber(int capacitate);

        //BC=AC=WC=theta(n)
		void redim();

    public:

	// constructorul implicit al dictionarului
	DO(Relatie r);

	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
    // BC=theta(1)
    // WC=O(n)
    // AC=theta(n)
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
    //BC=theta(1)
    //WC=O(n)
    //AC=theta(n)
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
    //BC=theta(1)
    //WC=O(n)
    //AC=theta(n)
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
    //BC=WC=AC=theta(1)
	int dim() const;

	//verifica daca dictionarul e vid
    //BC=WC=AC=theta(1)
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;

	// destructorul dictionarului
	~DO();

};
