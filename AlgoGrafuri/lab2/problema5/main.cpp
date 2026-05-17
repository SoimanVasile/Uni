#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

typedef vector<int> list_t;
typedef vector<list_t> matrix_t;

struct node {
    int start_time;
    int finish_time;
    int color;
};

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

int DFS_VISIT(int u, vector<node> &dfs, int timp, const matrix_t &adjacency_list) {
    dfs[u].color = 1;
    timp++;
    dfs[u].start_time = timp;

    for (int v : adjacency_list[u]) {
        if (dfs[v].color == 0) {
            timp = DFS_VISIT(v, dfs, timp, adjacency_list);
        }
    }

    dfs[u].color = 2;
    timp++;
    dfs[u].finish_time = timp;

    return timp;
}

void print_dfs(const vector<node> &dfs) {
    int id = 1;
    for (const auto &val : dfs) {
        std::cout << "Node " << id++ << ": " << val.start_time << " - " << val.finish_time << "\n";
    }
}

int main() {
    size_t number_of_nodes;
    matrix_t adjacency_list = read_adjacency_list(number_of_nodes);
    
    vector<node> dfs(number_of_nodes, {0, 0, 0});
    
    int timp = 0;
    int nod;
    std::cout<<"Citestes un nod";
    std::cin>>nod;
    timp = DFS_VISIT(nod-1, dfs, timp, adjacency_list);
    print_dfs(dfs);
    return 0;
}
