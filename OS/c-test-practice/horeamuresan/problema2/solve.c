#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **m, int rows, int cols, char *name) {

    int i, j;

    printf("Matrix %s:\n",name);

    for (i = 0; i < rows; i++) {

        for (j = 0; j < cols; j++) {

            printf("%d ", m[i][j]);

        }

        printf("\n");

    }

}



void sub(int **x, int **y, int **z, int rows, int cols) {

    int i, j;

    for (i = 0; i < rows; i++) {

        for (j = 0; j < cols; j++) {

            z[i][j] = x[i][j] - y[i][j];

        }

    }



}



int main(int argc, char **argv) {

    int **x, **y, rows, cols;

    FILE *f;



    if (argc != 2) {

        printf("Please provide one filename\n");

        exit(0);

    }



    f = fopen(argv[1], "r");



    fscanf(f, "%d %d", &rows, &cols);

    x = (int**)malloc(sizeof(int*) * rows);

    y = (int**)malloc(sizeof(int*) * rows);

    for (int i = 0; i < rows; i++) {

        x[i] = (int*)malloc(sizeof(int) * cols);

        y[i] = (int*)malloc(sizeof(int) * cols);

    }

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            fscanf(f, "%d", &x[i][j]);

        }

    }



    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            fscanf(f, "%d", &y[i][j]);

        }

    }



    fclose(f);



    printMatrix(x, rows, cols, "x");

    printMatrix(y, rows, cols, "y");



    int **z;

    z = (int**)malloc(sizeof(int*) * rows);

    for (int i = 0; i < rows; i++) {

        z[i] = (int*)malloc(sizeof(int) * cols);

    }

    sub(x, y, z, rows, cols);

    printMatrix(z, rows, cols, "x-y");



    for(int i = 0; i < rows; i++) {

        free(x[i]);

        free(y[i]);

		free(z[i]);

    }

    free(x);

    free(y);

	free(z);

    return 0;

}
