#pragma once

#define INIT_CAPACITY 2

typedef void* TElem;
typedef void (*DestroyFunction)(TElem);
typedef TElem (*CopyFunction)(TElem);

typedef struct {
    TElem* elements;
    int size;
    int capacity;
    DestroyFunction destFnc;
} MyList;

MyList* my_list_create(DestroyFunction destFnc);
void my_list_add_element(MyList *list, TElem elem);
void my_list_remove_by_index(MyList *list, int index);
void my_list_set_elem_by_index(MyList* list, int index, TElem elem);
int my_list_get_len(MyList *list);
TElem my_list_get_elem_by_index(MyList *list, int index);
TElem my_list_pop(MyList* list);
MyList* my_list_copy(MyList* list, CopyFunction copyFnc);
void my_list_swap(MyList* list, int i, int j);
void my_list_distruge(MyList *list);
