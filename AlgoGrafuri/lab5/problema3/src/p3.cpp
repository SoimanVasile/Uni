#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Error opening files!\n";
        return 1;
    }

    int V, E;
    if (!(fin >> V >> E)) return 0;

    // Adjacency list storing pairs of (neighbor, edge_id)
    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v;
        fin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vector<bool> used_edge(E, false);
    vector<int> path;
    vector<int> stack;

    // Find the first vertex with edges to start the cycle
    int start_node = 0;
    for (int i = 0; i < V; ++i) {
        if (!adj[i].empty()) {
            start_node = i;
            break;
        }
    }

    stack.push_back(start_node);

    // Textbook Hierholzer's Algorithm
    while (!stack.empty()) {
        int u = stack.back();
        
        if (!adj[u].empty()) {
            pair<int, int> edge = adj[u].back();
            adj[u].pop_back(); // Remove edge from current node's list
            
            // If the edge hasn't been traversed from the other side
            if (!used_edge[edge.second]) {
                used_edge[edge.second] = true;
                stack.push_back(edge.first);
            }
        } else {
            // No more untraversed edges from current node, add to path
            path.push_back(u);
            stack.pop_back();
        }
    }

    // Path is generated in reverse order
    for (size_t i = 0; i < path.size(); ++i) {
        fout << path[i];
        if (i + 1 < path.size()) fout << " ";
    }
    fout << "\n";

    return 0;
}
