#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

#define INF 1e9+7

typedef vector<int> list_t;
typedef vector<list_t> matrix_t;

matrix_t read_adjacency_list(size_t &number_of_nodes){
    std::ifstream fin("graf.txt");

    matrix_t adjacency_list;
    fin>>number_of_nodes;
    adjacency_list.resize(number_of_nodes, list_t());
    size_t x, y;
    while (fin>>x>>y){
        adjacency_list[x-1].push_back(y-1);
    }

    return adjacency_list;
}

list_t BFS(matrix_t adjacency_list, int number_of_nodes, int source){
    
    list_t queue;
    list_t shortest_road(number_of_nodes, INF);
    shortest_road[source] = 0;
    
    queue.push_back(source);
    int index = 0;
    while (index < queue.size()){
        for (auto vecini: adjacency_list[queue[index]]){
            if (shortest_road[vecini] == INF){
                queue.push_back(vecini);
                shortest_road[vecini] = shortest_road[queue[index]] + 1;
            }
        }
        index++;
    }

    return shortest_road;
}


void print_list_t(list_t list){
        for (auto val:list){
            std::cout<<val<<' ';
        }
}

int main(){
    size_t number_of_nodes;
    matrix_t adjacency_list = read_adjacency_list(number_of_nodes);
    list_t shortest_road = BFS(adjacency_list, number_of_nodes, 1);
    printf("Nodurile care au drum cu nodu sursa sunt:\n");
    for (size_t i=0; i<number_of_nodes; i++){
        if (shortest_road[i] != INF && shortest_road[i]!=0){
            std::cout<<i+1<<" si cu lungimea: "<<shortest_road[i]<<"\n";
        }
    }
    return 0;
}
