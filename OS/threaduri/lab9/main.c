#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

int rounds=0, count=0, players;
pthread_mutex_t m;
void* player(void* a){
    (void) a;

    while (1){
        pthread_mutex_lock(&m);
        if (*(int*)(a)==count){
            printf("%d\n", count);
            count=(count+1)%players;
            pthread_mutex_unlock(&m);
            break;
        }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}
int main(int argc, char** argv){
    if (argc < 2) {printf("Nu ati introdus numarul de jucatori!\n"); return 1;}
    players = atoi(argv[1]);
    pthread_mutex_init(&m, NULL);
    pthread_t* threads = (pthread_t*)malloc(players * sizeof(pthread_t));

    int* ids = (int*)malloc(sizeof(int) * players);
    for (int i=0; i<players; i++){
        ids[i]=i;
    }

    for (int i=0; i<10; i++){
        printf("Runda %d:\n", i);
        for (int j=0; j<players; j++){
            pthread_create(&threads[j], NULL, player, (void*)(&ids[j]));
        }

        for (int j=0; j<players; j++){
            pthread_join(threads[j], NULL);
        }
    }
    free(threads);
    free(ids);
    pthread_mutex_destroy(&m);
    return 0;
}
