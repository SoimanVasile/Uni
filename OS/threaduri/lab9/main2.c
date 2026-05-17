#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

#define number_of_rounds 10
int players=0;
int rounds=0;

pthread_mutex_t* m;
pthread_t* t;
void* f(void* a){

    int player_id = *(int*)(a);
    for (int i=0; i<number_of_rounds; i++){
        pthread_mutex_lock(&m[player_id]);
        printf("Player_id: %d -- Number: %d\n", player_id, player_id);
        pthread_mutex_unlock(&m[(player_id+1)%players]);
    }
    return NULL;
}
int main(int argc, char** argv){
    if (argc <2) {printf("Nu ati introdus numarul de jucatori!\n"); return 1;}

    players=atoi(argv[1]);
    m = (pthread_mutex_t*)malloc(players * sizeof(pthread_mutex_t));
    t = (pthread_t*)malloc(players * sizeof(pthread_t));
    int* id = (int*)malloc(players * sizeof(int));

    for (int i=0; i<players; i++){
        id[i]=i;
        pthread_mutex_init(&m[i], NULL);
    }

    for (int i=1; i<players; i++){
        pthread_mutex_lock(&m[i]);
    }

    for (int i=0; i<players; i++){
        pthread_create(&t[i], NULL, f, (void*)(&id[i]));
    }

    for (int i=0; i<players; i++){
        pthread_join(t[i], NULL);
    }

    return 0;
}
