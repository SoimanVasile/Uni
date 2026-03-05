#include <stdio.h>
#include <assert.h>


int verificare_prim(int x);
void test_prim(){
    int numere[20] = {4, 5, 10, 11, 7, 12, 1, -2, 2};
    int verificare[20] = {0, 1, 0, 1, 1, 0, 0, 0, 1};

    for (int i=0; i<9; i++){
        if (verificare_prim(numere[i]) != verificare[i]){
            assert(0);
        }
    }
    assert(1);
    printf("SUCCES");
    return;
}

int verificare_prim(int x){
    if (x<2) return 0;

    for (int i=2; i*i<=x; i++){
        if (x%i == 0) return 0;
    }

    return 1;
}
int main(int argc, char **argv){
    if (argc>1){
        if (argv[1][0] == 't'){
            test_prim();
            return 0;
        }
    }

    size_t number;

    scanf("%zu", &number);

    printf("Numareul %zu: %d", number, verificare_prim(number));
    return 0;
}
