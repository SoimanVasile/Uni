#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <stdlib.h>

#define INF (1e9+7)
using std::vector;

typedef vector<vector<size_t>> matrix_t;
typedef vector<size_t> list_t;

using std::cout;

matrix_t from_files_to_adjacency_matrix(size_t& number_of_nodes, size_t& number_of_edges){

    std::ifstream f("input.txt");
    matrix_t adjacency_matrix{};
    size_t i;
    f>>number_of_nodes;
    
    for (i=0; i<number_of_nodes; i++){
        list_t vec{};
        for (size_t j=0; j<number_of_nodes; j++)
            vec.push_back(0);
        adjacency_matrix.push_back(vec);
    }
    size_t x;
    size_t y;
    while (f>>x && f>>y){
        number_of_edges++;
        adjacency_matrix[x-1][y-1] = 1;
        adjacency_matrix[y-1][x-1] = 1;
    }

  return adjacency_matrix;
}

size_t grade_of_a_node(matrix_t adjacency_matrix, size_t number_of_nodes , size_t node){
    size_t grade{};
    for (size_t i=0; i<number_of_nodes; i++){
        if (adjacency_matrix[node][i])
        grade++;
    }
    return grade;
}

list_t find_the_isolated_nodes(matrix_t adjacency_matrix, size_t number_of_nodes){
    list_t isolated_nodes{};
    for (size_t i=0; i<number_of_nodes; i++){
        if (!grade_of_a_node(adjacency_matrix, number_of_nodes , i)){
        isolated_nodes.push_back(i+1);
    }
  }
  return isolated_nodes;
}

bool is_regular_graph(matrix_t adjacency_matrix, size_t number_of_nodes){
    size_t first_node_grade = grade_of_a_node(adjacency_matrix, number_of_nodes, 0);
    for (size_t i=1; i<number_of_nodes; i++){
        if (first_node_grade != grade_of_a_node(adjacency_matrix, number_of_nodes, i)) return false;
    }

    return true;
}

matrix_t create_routing_matrix(matrix_t adjacency_matrix, size_t number_of_nodes){
    matrix_t routing_matrix;
    for (size_t i=0; i<number_of_nodes; i++){
        list_t row;
        for (size_t j=0; j<number_of_nodes; j++){
            if (i == j) row.push_back(0);
            else if(adjacency_matrix[i][j] == 0) row.push_back(INF);
            else row.push_back(adjacency_matrix[i][j]);
        }
        routing_matrix.push_back(row);
    }

    for (size_t k=0; k<number_of_nodes; k++){
        for (size_t i=0; i<number_of_nodes; i++){
            if (i != k && routing_matrix[i][k] != INF){
                for (size_t j=0; j<number_of_nodes; j++){
                    if (j != k && routing_matrix[k][j] != INF){
                        routing_matrix[i][j] = std::min(routing_matrix[i][j], routing_matrix[i][k] + routing_matrix[k][j]);
                    }
                }
            }
        }
    }
    return routing_matrix;
}

matrix_t find_connected_components(matrix_t routing_matrix, size_t number_of_nodes){
    std::unordered_set<size_t> seen;
    matrix_t connected_graph;
    for (size_t i=0; i<number_of_nodes; i++){
        if (seen.end() == seen.find(i+1)){
            seen.insert(i+1);
            list_t row;
            row.push_back(i+1);
            for (size_t j=i+1; j<number_of_nodes; j++){
                if (routing_matrix[i][j] != INF && seen.end() == seen.find(j+1)){
                    row.push_back(j+1);
                    seen.insert(j+1);
                }
            }
            connected_graph.push_back(row);
        }
    }
    return connected_graph;
}

void print_matrix_t(matrix_t matrix){
    for (list_t row: matrix){
        for (size_t val: row){
            cout<<val<<' ';
        }
        cout<<"\n";
    }
        cout<<"\n";
}

void print_list_t(list_t list){
    for (auto val: list){
        cout<<val<<' ';
    }
    cout<<"\n";
        cout<<"\n";
}

int main(){
    size_t number_of_nodes{};
    size_t number_of_edges{};
    matrix_t adjacency_matrix = from_files_to_adjacency_matrix(number_of_nodes, number_of_edges);
    cout<<"Matricea de adiacenta:\n";
    print_matrix_t(adjacency_matrix);
    list_t isolated_nodes = find_the_isolated_nodes(adjacency_matrix, number_of_nodes);

    if (isolated_nodes.size() != 0) print_list_t(isolated_nodes);
    else cout<<"Nu exista noduri izolate.\n\n";


    if (is_regular_graph(adjacency_matrix, number_of_nodes)){
        cout<<"Este un graf regulat\n\n";
    }
    else {
        cout<<"Nu este un graf regulat\n\n";
    }
    matrix_t routing_matrix = create_routing_matrix(adjacency_matrix, number_of_nodes);
    print_matrix_t(routing_matrix);
    matrix_t connected_matrix = find_connected_components(routing_matrix, number_of_nodes);
    if (connected_matrix.size() == 1){
        cout<<"Graful este conex!";
    }
    else{
        cout<<"Graful nu este conex!";
    }
  return 0;
}
