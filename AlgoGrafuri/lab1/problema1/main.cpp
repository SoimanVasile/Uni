#include <fstream>
#include <vector>
#include <iostream>

using std::vector;

typedef vector<vector<size_t>> matrix_t;
typedef vector<size_t> list_t;

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

matrix_t from_adjacency_matrix_to_adjacency_list(size_t number_of_nodes, matrix_t adjacency_matrix){
  matrix_t adjacency_list{};

  for(size_t i=0; i<number_of_nodes; i++){
    list_t vec{};
    for (size_t j=0; j<number_of_nodes; j++){
      if (adjacency_matrix[i][j] == 1){
        vec.push_back(j+1);
      }
    }
    adjacency_list.push_back(vec);
  }

  return adjacency_list;
}

matrix_t from_adjacency_list_to_incidence_matrix(size_t number_of_nodes, size_t number_of_edges, matrix_t adjacency_list){
  matrix_t incidence_matrix{};
  
  for (size_t i=0; i<number_of_nodes; i++){
    list_t vec{};
    for (size_t j=0; j<number_of_edges; j++){
      vec.push_back(0);
    }
    incidence_matrix.push_back(vec);
  }
  size_t cnt = 0;
  for (size_t i=0; i<number_of_nodes; i++){
    for (auto j: adjacency_list[i]){
      if (j-1>i){
        incidence_matrix[j-1][cnt] = 1;
        incidence_matrix[i][cnt] = 1;
        cnt++;
      }
    }
  }

  return incidence_matrix;
}

matrix_t from_incidence_matrix_to_adjacency_list(size_t number_of_nodes, size_t number_of_edges, matrix_t incidence_matrix){
  matrix_t adjacency_list{};
  for (size_t i=0; i<number_of_nodes; i++){
    list_t vec;
    adjacency_list.push_back(vec);
  }
  
  for (size_t j=0; j<number_of_edges; j++){
    int first_node = -1;
    for (size_t i=0; i<number_of_edges; i++){
      if (incidence_matrix[i][j] == 1){
        if (first_node != -1){
          adjacency_list[i].push_back(first_node+1);
          adjacency_list[first_node].push_back(i+1);
          i=number_of_nodes;
        }
        first_node = i;
      }
    }
  }
  return adjacency_list;
}

matrix_t from_adjacency_list_to_adjacency_matrix (size_t number_of_nodes, matrix_t adjacency_list){
  matrix_t adjacency_matrix;

  for (size_t i=0; i<number_of_nodes; i++){
    list_t vec;
    for (size_t j=0; j<number_of_nodes; j++){
      vec.push_back(0);
    }
    adjacency_matrix.push_back(vec);
  }

  for (size_t i=0; i<number_of_nodes; i++){
    for (auto node: adjacency_list[i]){
      adjacency_matrix[i][node-1] = 1;
      adjacency_matrix[node-1][i] = 1;
    }
  }

  return adjacency_matrix;
}

void print_matrix(matrix_t matrix, size_t n){
  for (size_t i=0; i<n; i++){
    for (auto j: matrix[i])
      std::cout<<j<<' ';

    std::cout<<"\n";
  }
  std::cout<<"\n";
}

int main(){
  size_t number_of_nodes{};
  size_t number_of_edges{};
  matrix_t adjacency_matrix = from_files_to_adjacency_matrix(number_of_nodes, number_of_edges);
  print_matrix(adjacency_matrix, number_of_nodes);
  matrix_t adjacency_list = from_adjacency_matrix_to_adjacency_list(number_of_nodes, adjacency_matrix);
  print_matrix(adjacency_list, number_of_nodes);
  matrix_t incidence_matrix = from_adjacency_list_to_incidence_matrix(number_of_nodes, number_of_edges, adjacency_list);
  print_matrix(incidence_matrix, number_of_nodes);
  adjacency_list = from_incidence_matrix_to_adjacency_list(number_of_nodes, number_of_edges, incidence_matrix);
  print_matrix(adjacency_list, number_of_nodes);
  adjacency_matrix = from_adjacency_list_to_adjacency_matrix(number_of_nodes, adjacency_list);
  print_matrix(adjacency_matrix, number_of_nodes);
  return 0;
}
