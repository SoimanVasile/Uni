#include <iostream>
#include <vector>
#include <fstream>

using std::vector;

typedef vector<size_t> list_t;
typedef vector<list_t> matrix_t;

matrix_t read_adjacency_matrix(size_t &number_of_nodes){
    std::ifstream fin("graf.txt");

    fin>>number_of_nodes;
    matrix_t adjacency_matrix(number_of_nodes, list_t(number_of_nodes, 0));
    size_t x,y;
    while(fin>>x>>y){
        adjacency_matrix[x][y]=1;
    }
    return adjacency_matrix;
}

matrix_t matricea_inchiderii_tranzitive(matrix_t adjacency_matrix, size_t number_of_nodes){
    matrix_t matricea_inchiderii(number_of_nodes, list_t(number_of_nodes, 0));

    for (size_t i=0; i<number_of_nodes; i++){
        for (size_t j=0; j<number_of_nodes; j++){
            matricea_inchiderii[i][j] = adjacency_matrix[i][j];
        }
    }
    for (size_t i=0; i<number_of_nodes; i++)
        matricea_inchiderii[i][i]=1;


    for (size_t k=0; k<number_of_nodes; k++){
        for (size_t i=0; i<number_of_nodes; i++){
            if (i != k){
                for (size_t j=0; j<number_of_nodes; j++){
                    if (j!=i && j!=k){
                        if (matricea_inchiderii[i][k] == 1 && matricea_inchiderii[k][j] == 1){
                            matricea_inchiderii[i][j] = 1;
                        }
                    }
                }
            }
        }
    }
    return matricea_inchiderii;
}

void print_matrix_t(matrix_t matrix){
    for (auto line:matrix){
        for (auto val:line){
            std::cout<<val<<' ';
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

int main(){
    size_t number_of_nodes{};
    matrix_t adjacency_matrix = read_adjacency_matrix(number_of_nodes);
    matrix_t matricea_inchiderii = matricea_inchiderii_tranzitive(adjacency_matrix, number_of_nodes);
    print_matrix_t(matricea_inchiderii);
    return 0;
}
