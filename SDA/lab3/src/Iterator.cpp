#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO& lo) : lista(lo){
    elem = lista.head;
}

void Iterator::prim() {
	/* de adaugat */
    elem = lista.head;
}

void Iterator::urmator(){
    if (elem == nullptr) throw std::exception();
    elem = elem->next;
}

bool Iterator::valid() const{
	/* de adaugat */
    if (elem == nullptr) return false;
	return true;
}

TElement Iterator::element() const{
    if (elem == nullptr) throw std::exception();
	return elem->val;
}


