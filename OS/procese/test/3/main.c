#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int pid_son;
volatile int exit_while=0;

void signal_function_son(int signo){
    if (signo == SIGUSR1){
        kill(getppid(), SIGUSR2);
        exit(0);
    }
}

void signal_function_father(int signo){
    if (signo == SIGUSR1){
        kill(pid_son, SIGUSR1);
    }

    if(signo == SIGUSR2){
        int status;
        waitpid(pid_son, NULL, 0);
        exit_while=1;
    }

}

int main(){
    pid_son = fork();
    if(pid_son == 0){
        signal(SIGUSR1, signal_function_son);
        while(1){
            pause();
        }
    }

    signal(SIGUSR1, signal_function_father);
    signal(SIGUSR2, signal_function_father);
    while (!exit_while){
        pause();
    }

    printf("Sa terminat procesul fiu!\n");
    return 0;
}

