#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    for (int i=0; i<3; i++){
        printf("%d, %d\n", getpid(), getppid());
        if (fork() > 0){
            wait(0);
            exit(0);
        }
    }

}
