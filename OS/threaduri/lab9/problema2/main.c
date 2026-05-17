#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int valoare_globala = 0;
pthread_rwlock_t rwlock;

void* scriitor(void* arg) {
    int id = *(int*)arg;
    while(1){
    printf("Scriitorul %d: asteapta sa blocheze (wrlock)...\n", id);
    pthread_rwlock_wrlock(&rwlock);
    printf("Scriitorul %d: a prins lock-ul! Incrementeaza valoarea...\n", id);
    valoare_globala++;
    pthread_rwlock_unlock(&rwlock);
    }
    
    return NULL;
}

void* cititor(void* arg) {
    int id = *(int*)arg;
    while(1){
    printf("Cititorul %d: asteapta sa blocheze (rdlock)...\n", id);
    pthread_rwlock_rdlock(&rwlock);
    printf("Cititorul %d: a prins lock-ul! Valoarea este %d.\n", id, valoare_globala);
    pthread_rwlock_unlock(&rwlock);
    }
    
    return NULL;
}

int main() {
    int nr_scriitori = 5;
    int nr_cititori = 50;

    pthread_t t_scriitori[nr_scriitori];
    pthread_t t_cititori[nr_cititori];

    int id_scriitori[nr_scriitori];
    int id_cititori[nr_cititori];

    if (pthread_rwlock_init(&rwlock, NULL) != 0) {
        printf("Eroare la initializarea rwlock!\n");
        return 1;
    }
    for (int i = 0; i < nr_scriitori; i++) {
        id_scriitori[i] = i;
        pthread_create(&t_scriitori[i], NULL, scriitor, &id_scriitori[i]);
    }

    for (int i = 0; i < nr_cititori; i++) {
        id_cititori[i] = i;
        pthread_create(&t_cititori[i], NULL, cititor, &id_cititori[i]);
    }

    for (int i = 0; i < nr_scriitori; i++) {
        pthread_join(t_scriitori[i], NULL);
    }
    for (int i = 0; i < nr_cititori; i++) {
        pthread_join(t_cititori[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
