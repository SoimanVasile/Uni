#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int size) {

    int **mat = malloc(sizeof(int*) * size);

    for(int i = 0; i < size; i++) {

        mat[i] = (int*)malloc(sizeof(int) * size);

    }

    return mat;

}



void print_matrix_to_fileptr(FILE *file, int **mat, int size) {

    for(int i = 0; i < size; i++) {

        for(int j = 0; j < size; j++) {

            fprintf(file, "%4d", mat[i][j]);

        }

        fprintf(file, "\n");

    }

}



void deallocate_matrix(int **mat, int size) {

    for(int i = 0; i < size; i++) {

        free(mat[i]);

    }

    free(mat);

}





int main(int argc, char **argv) {

    if(argc != 2) {

        printf("The program requires exactly one argument\n");

        exit(1);

    }



    // open the file for reading

    FILE *in_file = fopen(argv[1], "r");

    if(NULL == in_file) {

        perror("Cannot open input file");

        exit(1);

    }



    int size = 0;

    fscanf(in_file, "%d", &size);



    fclose(in_file);

    if(0 >= size) {

        printf("Cannot create matrix with size %d since it is not positive.\n", size);

        exit(1);

    }


    int **mat = allocate_matrix(size);


    
    for(int i = 0; i < size; i++) {

        for(int j = 0; j < size; j++) {

            mat[i][j] = j - i;

        }

    }



    // open the file for writing

    FILE *out_file = fopen("out.txt", "w");

    if(NULL == out_file) {

        perror("Cannot open output file");

        exit(1);

    }




    print_matrix_to_fileptr(out_file, mat, size);


    fclose(out_file);



    deallocate_matrix(mat, size);

    return 0;

}


