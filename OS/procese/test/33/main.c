#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int a2b[2], a2c[2], b2a[2], c2a[2];

    if (fork() == 0){
        //B
        close(a2b[1]);
        close(a2c[1]);
        close(a2c[0]);
        close(b2a[0]);
        close(c2a[0]);
        close(c2a[1]);

        while (1){
            char* buffer;
            int size;
            read(a2b[0], &size, sizeof(int));
            read(a2b[0], buffer, size);
            
            char* vowels=(char*)malloc(size * sizeof(char));
            int size_vowels;
            for (int i=0; i<size; i++){
                char letter = buffer[i];
                if (letter>='A' && letter <='Z'){
                    letter = letter - 'A' + 'a';
                }

                int bitmask = 0b00000000000100000100000100010001;
                if ((bitmask & 1<<(letter - 'a')) != 1){
                    vowels[size_vowels++] = letter;
                }
            }
            vowels[size_vowels] = '\0';
            write(b2a[1], &size_vowels, sizeof(int));
            write(b2a[1], &vowels, size_vowels * sizeof(char));
            free(vowels);
        }
    }

    close(a2b[0]);
    close(b2a[1]);

    
}
