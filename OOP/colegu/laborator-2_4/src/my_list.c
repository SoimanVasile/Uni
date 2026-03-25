#include <stdlib.h>
#include "MyList.h"

MyList* my_list_create(DestroyFunction destFnc){
    MyList* list = malloc(sizeof(MyList));
    list->capacity = INIT_CAPACITY;
    list->elements = malloc(INIT_CAPACITY * sizeof(TElem));
    list->size = 0;
    list->destFnc = destFnc;
    return list;
}

void my_list_add_element(MyList *list, TElem elem){
    if (list->size >= list->capacity){
        int new_capacity = list->capacity * 2;
        list->elements = realloc(list->elements, new_capacity * sizeof(TElem));
        list->capacity = new_capacity;
    }
    list->elements[list->size] = elem;
    list->size++; 
}

void my_list_remove_by_index(MyList *list, int index){
    list->destFnc(list->elements[index]); 
    for (int i = index; i < list->size - 1; i++){
        list->elements[i] = list->elements[i+1]; 
    }
    list->size--;
}

void my_list_set_elem_by_index(MyList* list, int index, TElem elem) {
    list->destFnc(list->elements[index]); 
    list->elements[index] = elem;         
}

int my_list_get_len(MyList *list){
    return list->size;
}

TElem my_list_get_elem_by_index(MyList *list, int index){
    return list->elements[index];
}

TElem my_list_pop(MyList* list) {
    if (list->size == 0) return NULL;
    TElem elem = list->elements[list->size - 1];
    list->size--;
    return elem;
}

MyList* my_list_copy(MyList* list, CopyFunction copyFnc) {
    MyList* newList = my_list_create(list->destFnc);
    for (int i = 0; i < list->size; i++) {
        my_list_add_element(newList, copyFnc(list->elements[i]));
    }
    return newList;
}

void my_list_swap(MyList* list, int i, int j) {
    TElem aux = list->elements[i];
    list->elements[i] = list->elements[j];
    list->elements[j] = aux;
}

void my_list_distruge(MyList *list){
    for (int i = 0; i < list->size; i++){
        list->destFnc(list->elements[i]);
    }
    free(list->elements);
    free(list);
}
