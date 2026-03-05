#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int size;
  int number_of_elements;
} HEADER;

#define ARR_INIT_CAPACITY 256

#define arr_push(arr,val)\
  do {\
    if ((arr) == NULL){ \
      HEADER* header = (HEADER*)malloc(ARR_INIT_CAPACITY * sizeof(*(arr)) + sizeof(HEADER)); \
      header->size = ARR_INIT_CAPACITY; \
      header->number_of_elements = 0; \
      arr = (void*)(header+1); \
    } \
    HEADER* header = (HEADER*)(arr) - 1;\
    if (header->number_of_elements == header->size)\
      assert(0);\
    (arr)[header->number_of_elements++] = (val);\
  } while(0)

#define arr_len(arr) ((HEADER*)(arr)-1)->number_of_elements

uint8_t arr_rem(int* arr, int val){

  size_t i = 0;
  while (i<arr_len((arr)) && (arr)[i]!=(val)){
    i++;
  } 
  if (i==arr_len((arr))) return 0;
  for (; i<arr_len((arr)); i++){
    (arr)[i] = (arr)[i+1];
  }
  ((HEADER*)arr - 1)->number_of_elements--;
  return 1;
}

int main(){
  int* numbers = NULL;
  arr_push(numbers, 20);
  arr_push(numbers, 1250);
  arr_push(numbers, 305);
  arr_push(numbers, 431);
  for (size_t i=0; i<arr_len(numbers); i++){
    printf("%d ", numbers[i]);
  }
  printf("\n");
  if (!arr_rem(numbers,20)) {printf("Nu exista valoarea");}
  for (size_t i=0; i<arr_len(numbers); i++){
    printf("%d ", numbers[i]);
  }
  printf("\n");
  (void)numbers;
}
