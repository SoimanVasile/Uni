#include "Iterator.h"
#include "node.h"
#include "LO.h"

#include <exception>

LO::LO(Relatie r) {
	/* de adaugat */
    relatie = r;
    head = NULL;
    size = 0;
}

// returnare dimensiune
int LO::dim() const {
	/* de adaugat */
	return size;
}

// verifica daca LO e vida
bool LO::vida() const {
	/* de adaugat */
    if (size != 0) return false;
	return true;
}

// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const{
	/* de adaugat */
    if (i<0 || i>=size) throw std::exception();

    int index{};
    node* node_t= head;
    while (index < i){
        index++;
        node_t = node_t->next;
    }
	return node_t->val;
    
}

// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {

    if (i<0 || i>=size) throw std::exception();
    
    TElement val;
    if (i == 0) {
        val = head->val;
        node* to_delete = head;
        head = head->next;
        delete to_delete;
        size--;
        return val;
    }
    
    int index = 0;
    node* node_t = head;
    while (index < i-1){
        node_t = node_t->next;
        index++;
    }
    
    node* to_delete = node_t->next;
    val = to_delete->val;
    node_t->next = to_delete->next;
    delete to_delete;
    size--;
    return val;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
    node* node_t = head;
    int index = 0;
    while (node_t != NULL && node_t->val != e){
        node_t = node_t->next;
        index++;
    }
    if (node_t != NULL && node_t->val == e) return index;
	return -1;
}

// adaugare element in LO
void LO::adauga(TElement e) {
    if (head == NULL){
        head = new node;
        head->next = NULL;
        head->val = e;
        size++;
        return;
    }

    if (!relatie(head->val, e)) {
        node* new_node = new node;
        new_node->val = e;
        new_node->next = head;
        head = new_node;
        size++;
        return;
    }

    node* node_t=head;
    while (node_t->next != NULL && relatie(node_t->next->val, e)){
        node_t = node_t->next;
    }
    node* new_node = new node; 
    new_node->val = e;
    new_node->next = node_t->next;
    node_t->next = new_node;
    size++;
}

// returnare iterator
Iterator LO::iterator(){
	return Iterator(*this);
}


//destructor
LO::~LO() {
    node* current = head;
    while (current != NULL) {
        node* next_node = current->next;
        delete current;
        current = next_node;
    }
}
