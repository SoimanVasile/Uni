#include <iostream>
#include <fstream>
#include <vector>

#define INFINITY 1e9+7
using std::vector;

typedef vector<size_t> list_t;
typedef vector<list_t> matrix_t;

matrix_t read_adjacency_list(size_t &number_of_nodes, size_t &number_of_edges){
    std::ifstream fin("graf.txt");

    matrix_t adjacency_list;
    fin>>number_of_nodes;
    adjacency_list.resize(number_of_nodes, list_t());
    size_t x, y;
    while (fin>>x>>y){
        adjacency_list[x-1].push_back(y-1);
        adjacency_list[y-1].push_back(x-1);
        number_of_edges++;
    }

    return adjacency_list;
}

matrix_t MOORE(matrix_t &adjacency_list, size_t source){
    list_t shortest_road(adjacency_list.size(), INFINITY);
    list_t parent_vector(adjacency_list.size(), -1);
    shortest_road[source] = 0;
    parent_vector[source] = -1;

    list_t queue;

    queue.push_back(source);

    size_t index=0;

    while(index<queue.size()){
        size_t x = queue[index];
        for (size_t neighbour : adjacency_list[x]){
            if (shortest_road[neighbour] == INFINITY){
                parent_vector[neighbour] = x;
                shortest_road[neighbour] = shortest_road[x]+1;
                queue.push_back(neighbour);
            }
        }
        index++;
    }

    matrix_t result;
    result.push_back(shortest_road);
    result.push_back(parent_vector);
    return result;
}

int main(){
    size_t number_of_nodes{},number_of_edges{};
    matrix_t adjacency_list = read_adjacency_list(number_of_nodes, number_of_edges);
    matrix_t moore = MOORE(adjacency_list, 3);
    for (size_t i=0; i<number_of_nodes; i++){
        list_t road;
        int z=i;
        while (z != -1){
            road.push_back(z+1);
            z = moore[1][z];
        }
        for (int j=road.size()-1; j>=0; j--){
            std::cout<<road[j]<<' ';
        }
        std::cout<<"\n";
    }
}
