#include <array>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#define inf 1000000007
typedef struct {
    int distance;
    int parent;
    int index;
} node;

void initializare_S(std::vector<node>& V, int source){
    int i{};
    for (auto& n : V){
        n.distance = inf;
        n.parent = -1;
        n.index = i++;
    }
    V[source].distance = 0;
}

void relax(int w, const node& u, node& v){
    if (u.distance != inf && v.distance > u.distance + w){
        v.distance = u.distance + w;
        v.parent = u.index;
    }
}

bool Bellman_Ford(std::vector<std::array<int, 3>> list_of_edges, int source, int number_of_nodes, std::vector<node>& V){
    initializare_S(V, source);
    for (int i=0; i<number_of_nodes-1; i++){
        for (auto edge : list_of_edges ){
            relax(edge[2], V[edge[0]], V[edge[1]]);
        }
    }

    for (auto edge : list_of_edges){
        if (V[edge[0]].distance != inf && V[edge[1]].distance > (V[edge[0]].distance + edge[2])){
            return false;
        }
    }
    return true;

}

int main(int argc, char** argv){
    if (argc != 3){
        std::cout<<"Nu ati introdus fisierele!";
        exit(1) ;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    int number_nodes;
    int number_edges, source;
    fin>>number_nodes>>number_edges>>source;
    std::vector<std::array<int, 3>> list_of_edges(number_edges);
    for (int i=0; i<number_edges; i++){
        fin>>list_of_edges[i][0];
        fin>>list_of_edges[i][1];
        fin>>list_of_edges[i][2];
    }

    std::vector<node> V(number_nodes, node());
    Bellman_Ford(list_of_edges, source, number_nodes, V);

    for (auto val : V){
        if (val.distance == inf) {
            fout << "INF ";
        } else {
            fout << val.distance << ' ';
        }
    }

    fin.close();
    fout.close();
    return 0;
}
