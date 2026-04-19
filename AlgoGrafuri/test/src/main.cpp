#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int INF = 1e9;

bool bellman_ford(int start, int number_of_nodes, vector<vector<pair<int, int>>>& adj, vector<int>& dist, vector<int>& parent) {
    
    dist[start] = 0;

    for (int i = 1; i <= number_of_nodes - 1; i++) {
        bool changed = false;
        for (int u = 0; u < number_of_nodes; u++) {
            if (dist[u] == INF) continue;

            for (auto edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    for (int u = 0; u < number_of_nodes; u++) {
        if (dist[u] == INF) continue;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                return false; 
            }
        }
    }

    return true;
}

void read_adjacency_list(vector<vector<pair<int, int>>> &adjacency_list, int &number_of_nodes, int &number_of_edges, char* path){
    ifstream fin(path);
    fin>>number_of_nodes;
    fin>>number_of_edges;
    adjacency_list.resize(number_of_nodes);
    int source, target, weight;
    for (int i=0; i<number_of_edges; i++){
        if (!(fin >> source >> target >> weight)) break;
        if (source >= 0 && source < number_of_nodes && target >= 0 && target < number_of_nodes) {
            adjacency_list[source].push_back(std::make_pair(target, weight));
        } else {
            cerr << "Warning: Edge (" << source << ", " << target << ") is outside the valid node range [0, " << number_of_nodes - 1 << "]. Skipping.\n";
        }
    }
}

int main(int argc, char** argv){
    if (argc != 2){
        cout<<"Nu ai dat input de intrare!\n";
        return 1;
    }

    vector<vector<pair<int, int>>> adjacency_list;
    int number_of_nodes, number_of_edges;
    read_adjacency_list(adjacency_list, number_of_nodes, number_of_edges, argv[1]);
    vector<int> dist(number_of_nodes, INF);
    vector<int> parent(number_of_nodes, -1);
    int X, Y;
    cout<<"Citeste X: ";
    cin>>X;
    cout<<"Citeste Y: ";
    cin>>Y;
    if ((X>=number_of_nodes || X<0 )|| (Y>=number_of_nodes || Y<0)){
        cout<<"X si Y nu sunt in rangeul nodurilor!\n";
        return 1;
    }
    if (bellman_ford(X, number_of_nodes, adjacency_list, dist, parent) == false){
        cout<<"Eroare: Exista un ciclu negativ!\n";
        return 0;
    }

    if (dist[Y] == INF){
        cout<<"Nu exista drum de la X la Y!\n";
        return 1;
    }
    int node=Y;
    vector<int> drum;
    while (node != -1){
        drum.push_back(node);
        node = parent[node];
    }
    cout<<"Cel mai scurt drum de la X la Y este de cost "<<dist[Y]<<" : ";
    for (int i=drum.size()-1; i>=0; i--){
        cout<<drum[i]<<' ';
    }
    return 0;
}
