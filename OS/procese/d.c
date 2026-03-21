#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    printf("%d %d a\n", getpid(), getppid());
    for (int i =0; i<3; i++){
        if (fork()==0){
            printf("Fiu %d %d %d b\n", getpid(), getppid(), i);
            exit(0);
        }
    }

    for (int i =0; i<3; i++){
    wait(NULL);
    }
    printf("%d %d b\n", getpid(), getppid());
    (void)argc;
    (void)argv;
    return 0;
}
