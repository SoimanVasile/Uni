#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    int weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
            return true;
        }
        return false;
    }
};

void solve(char* input_file, char* output_file) {
    ifstream fin(input_file);
    if (!fin.is_open()) {
        cerr << "Error opening input file!\n";
        return;
    }

    int V, E;
    if (!(fin >> V >> E)) return;

    vector<Edge> edges(E);
    for (int i = 0; i < E; ++i) {
        fin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    fin.close();

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    DSU dsu(V);
    int mst_weight = 0;
    vector<pair<int, int>> mst_edges;

    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mst_weight += edge.weight;
            mst_edges.push_back({edge.u, edge.v});
            if (mst_edges.size() == static_cast<size_t>(V - 1)) {
                break; // MST has V-1 edges
            }
        }
    }

    ofstream fout(output_file);
    if (!fout.is_open()) {
        cerr << "Error opening output file!\n";
        return;
    }

    fout << mst_weight << "\n";
    fout << mst_edges.size() << "\n";
    for (const auto& edge : mst_edges) {
        fout << edge.first << " " << edge.second << "\n";
    }
    fout.close();
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    solve(argv[1], argv[2]);

    return 0;
}
