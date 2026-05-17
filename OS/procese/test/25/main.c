#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int main(int argc, char** argv){
    (void)argc;
    (void)argv;
    srand(time(NULL));
    int a2d[2], b2d[2], c2d[2];
    pipe(a2d);
    pipe(b2d);
    pipe(c2d);

    
signal(SIGPIPE, SIG_IGN);
    if (fork() == 0){
        srand(time(NULL) ^ (getpid() << 16));
        // child D
        close(a2d[1]);
        close(b2d[1]);
        close(c2d[1]);

        while(1){
            int read_A;
            int read_B;
            int read_C;
            read(a2d[0], &read_A, sizeof(int));
            read(b2d[0], &read_B, sizeof(int));
            read(c2d[0], &read_C, sizeof(int));

            int diff = read_B - read_C;


            if (diff < 0 ){
                diff *=-1;
            }

            printf("Diff: %d ------ A: %d\n", diff, read_A);

            if (diff <= read_A){
                close(a2d[0]);
                close(b2d[0]);
                close(c2d[0]);
                break;
            }
        }
        exit(0);
    }

    close(a2d[0]);
    close(b2d[0]);
    close(c2d[0]);
    if (fork() == 0){
        srand(time(NULL) ^ (getpid() << 16));
        close(a2d[1]);
        close(c2d[1]);
        while (1){
            int number = rand()%200 + 1;
            if (write(b2d[1], &number, sizeof(int))<0){
                close(b2d[1]);
                break;
            }
        }
        exit(0);
    }

    if (fork() == 0){
        srand(time(NULL) ^ (getpid() << 16));
        close(a2d[1]);
        close(b2d[1]);
        while (1){
            int number = rand()%200 + 1;
            if (write(c2d[1], &number, sizeof(int))<0){
                close(c2d[1]);
                break;
            }
        }
        exit(0);
    }
    
        close(b2d[1]);
        close(c2d[1]);
        while (1){
            int number = rand()%11 + 10;
            if (write(a2d[1], &number, sizeof(int))<0){
                close(a2d[1]);
                printf("Closed!\n");
                break;
            }
        }

        for(int i=0; i<3; i++){
            wait(0);
        }
    return 0;
}
