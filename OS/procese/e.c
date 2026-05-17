#include <stdio.h>
#include <signal.h>

void  f(int sgn){
    printf("Nigga balls\n");
    (void)sgn;
}

int main(int argc, char** argv){
    signal(SIGINT, f);
    while(1);
    (void)argc;
    (void)argv;
    return 0;
}
