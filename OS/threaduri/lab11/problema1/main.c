#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if (argc != 1) {printf("Nu trebuie argumente!\n"); return 1;}

    int* vector = (int*)malloc(100000 * sizeof(int));

    pthread_t* threads = (pthread_t*)malloc(100 * sizeof(pthread_t));

    int number_of_elements = 100000/100;

    int* ids = (int*)malloc(100 * sizeof(int));
    for (int i=0; i<100; i++){
        
    }
    for (int i=0; i<100; i++){

    }

    free(vector);
    free(threads);
    return 0;
}
