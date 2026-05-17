#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

int pipe_citire_fiu;

void handle_signal(int signio){
    if (signio==SIGUSR1){
        close(pipe_citire_fiu);
        printf("Semnal primit! Fiul sa incheiat!\n");
        exit(0);
    }
}

int main(){
    
    int pid[3];
    int pipe_child[3][2];
    pipe(pipe_child[0]);
    pipe(pipe_child[1]);
    pipe(pipe_child[2]);
    for (int i=0; i<3; i++){
        pid[i] = fork();
        if (pid[i] == 0){
            for (int j=0; j<3; j++){
                if (j!=i){
                    close(pipe_child[j][1]);
                    close(pipe_child[j][0]);
                }
            }

            pipe_citire_fiu = pipe_child[i][0];

            signal(SIGUSR1, handle_signal);
            close(pipe_child[i][1]);
            char buffer[256];
            while(1){
                int bytes_read = read(pipe_child[i][0], buffer, sizeof(buffer));
                if (bytes_read > 0) {
                    printf("Fiul %d a primit: %s\n", i, buffer);
                } else {
                    break; 
                }
            }
            close(pipe_child[i][0]);
            exit(0);
        }
    }

    close(pipe_child[0][0]);
    close(pipe_child[1][0]);
    close(pipe_child[2][0]);

    int count=0;
    while (1){
        char buffer[256];
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        buffer[strcspn(buffer, "\n")] = 0; 
        if (strcmp(buffer, "stop") == 0) {
            for (int i=0; i<3; i++){
                kill(pid[i], SIGUSR1);
            }
            for (int i=0; i<3; i++){
                wait(0);
            }
            break;
        }
        write(pipe_child[count][1], buffer, strlen(buffer) + 1);
        count = (count+1)%3;
    }

    sleep(20);
    close(pipe_child[0][1]);
    close(pipe_child[1][1]);
    close(pipe_child[2][1]);
}
