#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1
#include "node.h"
class LO {
private:
	friend class Iterator;
private:
	/* aici e reprezentarea */
    Relatie relatie;
    node* head;
    int size;
public:
	// constructor
	LO(Relatie r);

	// returnare dimensiune
    // Best Case = Worst Case = Avg Case = theta(1)
	int dim() const;

	// verifica daca LO e vida
    // Best Case = Worst Case = Avg Case = theta(1)
	bool vida() const;

	// returnare element
	//arunca exceptie daca i nu e valid
    //Best Case = Theta(1)
    //Worst Case = O(n)
    //Avg Case = Theta(i)
	TElement element(int i) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
    // Best Case = theta(1)
    // Worst Case = O(n)
    // Avg Case = theta(n)
	void adauga(TElement e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
    //Best Case = theta(1)
    //Worst Case = O(n)
    //Avg Case = theta(i)
	TElement sterge(int i);

	// cauta element si returneaza prima pozitie pe care apare (sau -1)
    // Best Case = theta(1)
    // Worst Case = O(n)
    // Avg Case = theta(n)
	int cauta(TElement e) const;

	// returnare iterator
	Iterator iterator();

	//destructor
	~LO();

};
