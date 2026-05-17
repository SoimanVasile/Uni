#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    printf("%d %d a\n", getpid(), getppid());
    for (int i =0; i<3; i++)
        fork();
    printf("%d %d b\n", getpid(), getppid());
    (void)argc;
    (void)argv;
    return 0;
}
