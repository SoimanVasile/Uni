#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1000000000

void read_adjacency_list(std::vector<std::vector<std::pair<int, int>>>& adjacency_list, int& number_of_nodes, int& number_of_edges, std::ifstream& fin){
    fin>>number_of_nodes;
    fin>>number_of_edges;
    adjacency_list.resize(number_of_nodes);
    for(int i=0; i<number_of_edges; i++){
        int source, target, weight;
        fin>>source>> target>> weight;
        adjacency_list[source].push_back(std::pair<int, int>(target, weight));
    }
}

void Bellmand_Ford_initializare(std::vector<std::pair<int, int>>& v, int source){
    for (auto& node : v){
        node.first = -1;
        node.second = INF;
    }
    v[source].second = 0;
}

void Bellman_Ford_relax(std::vector<std::pair<int, int>>& v, int u, int q, int w){
    if (v[u].second != INF && v[q].second > v[u].second + w){
        v[q].second = v[u].second + w;
        v[q].first = u;
    }
}

bool Bellman_Ford(std::vector<std::vector<std::pair<int, int>>> const& adjacency_list, std::vector<std::pair<int, int>>& v, int source){
    v.resize(adjacency_list.size());
    Bellmand_Ford_initializare(v, source);
    
    int n = adjacency_list.size();
    for (int j=0; j<n-1; j++){
        for (int u=0; u<n; u++){
            auto const& list = adjacency_list[u];
            for (auto const& edge : list){
                Bellman_Ford_relax(v, u, edge.first, edge.second);
            }
        }
    }

    for (int u=0; u<n; u++){
        auto const& list = adjacency_list[u];
        for (auto const& edge : list){
            if (v[u].second != INF && v[edge.first].second > v[u].second + edge.second){
                return false; 
            }
        }
    }
    return true;
}

void Dijkstra(std::vector<std::vector<std::pair<int, int>>> const& adjacency_list, int source, std::vector<std::pair<int, int>>& v){
    int n = adjacency_list.size();
    v.assign(n, {-1, INF});
    v[source].second = 0;
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (dist > v[u].second) continue;
        
        for (auto const& edge : adjacency_list[u]) {
            int target = edge.first;
            int weight = edge.second;
            
            if (v[target].second > v[u].second + weight) {
                v[target].second = v[u].second + weight;
                v[target].first = u;
                pq.push({v[target].second, target});
            }
        }
    }
}

void Johnson(std::vector<std::vector<std::pair<int, int>>>& adjacency_list, std::ofstream& fout){
    int n = adjacency_list.size();
    
    for (int i = 0; i < n; i++) {
        std::sort(adjacency_list[i].begin(), adjacency_list[i].end());
    }
    
    std::vector<std::vector<std::pair<int, int>>> aug_list = adjacency_list;
    aug_list.push_back({});
    for (int i = 0; i < n; i++) {
        aug_list[n].push_back({i, 0});
    }
    
    std::vector<std::pair<int, int>> h;
    bool no_negative_cycle = Bellman_Ford(aug_list, h, n);
    
    if (!no_negative_cycle) {
        fout << -1 << "\n";
        return;
    }
    
    for (int u = 0; u < n; u++) {
        for (auto& edge : adjacency_list[u]) {
            int target = edge.first;
            edge.second = edge.second + h[u].second - h[target].second;
            
            fout << u << " " << target << " " << edge.second << "\n";
        }
    }
    
    for (int u = 0; u < n; u++) {
        std::vector<std::pair<int, int>> dijkstra_dist;
        Dijkstra(adjacency_list, u, dijkstra_dist);
        
        for (int target = 0; target < n; target++) {
            if (dijkstra_dist[target].second == INF) {
                fout << "INF ";
            } else {
                int actual_dist = dijkstra_dist[target].second + h[target].second - h[u].second;
                fout << actual_dist << " ";
            }
        }
        fout << "\n";
    }
}

int main(int argc, char** argv){
    if (argc != 3){
        std::cout<<"Nu ai introdus fisierele!\n";
        return 1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    int number_of_nodes, number_of_edges;
    std::vector<std::vector<std::pair<int, int>>> adjacency_list;
    read_adjacency_list(adjacency_list, number_of_nodes, number_of_edges, fin);

    Johnson(adjacency_list, fout);
    
    fin.close();
    fout.close();
    return 0;
}
