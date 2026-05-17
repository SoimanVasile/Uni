#include "IteratorMDO.h"
#include "MDO.h"

#include <exception>

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	curente.resize(dict.m);
	prim();
}

void IteratorMDO::prim(){
	for (int i = 0; i < dict.m; ++i) {
		curente[i] = dict.tabela[i];
	}
	nod_curent = nullptr;
	for (int i = 0; i < dict.m; ++i) {
		if (curente[i] != nullptr) {
			if (nod_curent == nullptr || dict.rel(curente[i]->elem.first, nod_curent->elem.first)) {
				nod_curent = curente[i];
			}
		}
	}
}

void IteratorMDO::urmator(){
	if (!valid()) {
		throw std::exception();
	}
	int poz = dict.d(nod_curent->elem.first);
	curente[poz] = curente[poz]->urm;
	
	nod_curent = nullptr;
	for (int i = 0; i < dict.m; ++i) {
		if (curente[i] != nullptr) {
			if (nod_curent == nullptr || dict.rel(curente[i]->elem.first, nod_curent->elem.first)) {
				nod_curent = curente[i];
			}
		}
	}
}

bool IteratorMDO::valid() const{
	return nod_curent != nullptr;
}

TElem IteratorMDO::element() const{
	if (!valid()) {
		throw std::exception();
	}
	return nod_curent->elem;
}


