#include <iostream>
#include <fstream>
#include <vector>

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

size_t grade_of_a_node(size_t number_of_nodes, matrix_t adjacency_matrix, size_t node){
  size_t grade{};
  for (size_t i=0; i<number_of_nodes; i++){
    if (adjacency_matrix[node][i])
      grade++;
  }
  return grade;
}

list_t find_the_isolated_nodes(size_t number_of_nodes, matrix_t adjacency_matrix){
  list_t isolated_nodes{};
  for (int i=0; i<number_of_nodes; i++){
    if (!grade_of_a_node(number_of_nodes, adjacency_matrix, i)){
      isolated_nodes.push_back(i+1);
    }
  }
  return isolated_nodes;
}

void print_list_t(list_t list){
  for (auto val: list){
    cout<<val<<' ';
  }
  cout<<"\n";
}

int main(){
  size_t number_of_nodes{};
  size_t number_of_edges{};
  matrix_t adjacency_matrix = from_files_to_adjacency_matrix(number_of_nodes, number_of_edges);
  list_t isolated_nodes = find_the_isolated_nodes(number_of_nodes, adjacency_matrix);
  print_list_t(isolated_nodes);
  return 0;
}
