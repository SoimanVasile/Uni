#include <iostream>
#include <fstream>
#include <vector>

#define INF 1000000007
using std::vector;

typedef vector<int> list_t;
typedef vector<list_t> matrix_t;

matrix_t read_adjacency_list(int &number_of_nodes){
    std::ifstream fin("graf.txt");

    matrix_t adjacency_list;
    fin>>number_of_nodes;
    adjacency_list.resize(number_of_nodes, list_t());
    int x, y;
    while (fin>>x>>y){
        adjacency_list[x-1].push_back(y-1);
    }

    return adjacency_list;
}

matrix_t MOORE(matrix_t &adjacency_list, int source){
    list_t shortest_road(adjacency_list.size(), INF);
    list_t parent_vector(adjacency_list.size(), -1);
    shortest_road[source] = 0;
    parent_vector[source] = -1;

    list_t queue;

    queue.push_back(source);

    int index=0;

    while(index<(int)queue.size()){
        int x = queue[index];
        for (int neighbour : adjacency_list[x]){
            if (shortest_road[neighbour] == INF){
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
    int number_of_nodes{};
    matrix_t adjacency_list = read_adjacency_list(number_of_nodes);
    int nod;
    std::cout<<"Citeste nod: ";
    std::cin>>nod;
    matrix_t moore = MOORE(adjacency_list, nod-1);
    for (int i=0; i<number_of_nodes; i++){
        list_t road;
        int z=i;
        if (moore[0][z] == INF){
            std::cout<<i+1<<" este nod izolat!\n";
            continue;
        }
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
