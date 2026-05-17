#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("Hei");
    // mkfifo("a2b", 0600);
    // mkfifo("b2a", 0600);
    int a2b = open("a2b", O_WRONLY);
    int b2a = open("b2a", O_RDONLY);
    printf("Hei2");
    int number=0;
    while (number != 10){
        number=rand()%10 + 1;
        write(a2b, &number, sizeof(int));
        int read_number;
        read(b2a, &read_number, sizeof(int));
        printf("Procesul2: %d\n", read_number);
    }
    
    close(a2b); close(b2a);
    // unlink("a2b");
    // unlink("b2a");
    return 0;
}
