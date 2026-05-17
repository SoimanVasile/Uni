#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int a2b = open("a2b", O_RDONLY);
    int b2a = open("b2a", O_WRONLY);

    int number=0;
    while (number != 10){
        int read_number;
        read(a2b, &read_number, sizeof(int));
        printf("Procesul2: %d\n", read_number);
        number=rand()%10 + 1;
        write(b2a, &number, sizeof(int));
    }
    
    close(a2b); close(b2a);

    return 0;
}
