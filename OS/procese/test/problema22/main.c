#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(){
    struct timeval start, end;

    gettimeofday(&start, NULL);

    for (int i=0; i<10; i++){
        if (fork() == 0){
            sleep(1);
            exit(0);
        }
        wait(0);
    }

    gettimeofday(&end, NULL);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Total execution time: %f seconds\n", elapsed_time);

    return 0;
}
