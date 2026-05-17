#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    int a2b[2], b2c[2], c2a[2];
    pipe(a2b); pipe(b2c); pipe(c2a);
    if (fork() == 0){
        close(a2b[1]);
        int size;
        read(a2b[0], &size, sizeof(int));
        int* vector = (int*)malloc(size * sizeof(int));
        int i=0;
        while (i<size){
            int number;
            read(a2b[0], &number, sizeof(int));
            printf("primit B: %d\n", number);
            int random = rand()%4 + 2;
            number+=random;
            vector[i]=number;
            i++;
        }
        close(a2b[0]);

        if (fork() == 0){
            close (b2c[1]);
            close (c2a[0]);
            int sum=0;
            for (int i=0; i<size; i++){
                int read_number;
                read(b2c[0], &read_number, sizeof(int));
                sum+=read_number;
            }
            close(b2c[0]);
            printf("trimis C: %d\n", sum);
            write(c2a[1], &sum, sizeof(int));
            close(c2a[1]);
            return 0;
        }
        close(b2c[0]);
        close(c2a[0]);
        close(c2a[1]);
        for (int i=0; i<size; i++){
            printf("trimis B: %d\n", vector[i]);
            write(b2c[1], &vector[i], sizeof(int));
        }
        close(b2c[1]);
        return 0;
    }

    close(a2b[0]);
    close(b2c[0]);
    close(b2c[1]);
    close(c2a[1]);
    int size=argc-1;
    write(a2b[1], &size, sizeof(int));
    int i=1;
    while (i<argc){
        int number = atoi(argv[i]);
        printf("trimis A: %d\n", number);
        write(a2b[1], &number, sizeof(int));
        i++;
    }

    int read_number;
    read(c2a[0], &read_number, sizeof(int));
    printf("primit A: %d\n", read_number);
    close(a2b[1]);
}
