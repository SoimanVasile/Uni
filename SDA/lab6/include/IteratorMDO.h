#pragma once

#include "MDO.h"


class IteratorMDO{
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;
	/* aici e reprezentarea  specifica a iteratorului */
	vector<MDO::Nod*> curente;
	MDO::Nod* nod_curent;
public:

	    // reseteaza pozitia iteratorului la inceputul containerului
        // BC = WC = AC = theta(m)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
        // BC = WC = AC = theta(m)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
        // BC = WC = AC = theta(1)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
        // BC = WC = AC = theta(1)
		TElem element() const;
};

