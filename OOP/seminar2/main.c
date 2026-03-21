#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    char** brad;


    scanf("%d", &n);

    brad = (char**)malloc(sizeof(char*) * n);
    for (int i=0; i<n; i++){
        brad[i] = (char*)malloc(sizeof(char) * (2*i+2));
        for (int j=0; j<2*i+1; j++){
            brad[i][j] = '*';
        }
        brad[i][2*i+1] = '\0';
    }

    for (int i=0; i<n; i++){
        printf("%*s\n", n+i, brad[i]);
    }

    for (int i=0; i<n; i++)
        free(brad[i]);

    free(brad);
    return 0;
}
