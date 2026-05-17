#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char** argv){
    (void)argv;
    (void) argc;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    if (fork()==0){
        execvp(argv[1], argv+1);
    }
    wait(0);
    gettimeofday(&end, NULL);
    double time_taken = start.tv_sec - end.tv_sec - (start.tv_usec - end.tv_usec)/1000000.0;
    printf("Time taken : %f", time_taken);
    return 0;
}
