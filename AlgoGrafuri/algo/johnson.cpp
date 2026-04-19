#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

// Assume bellman_ford and dijkstra functions are defined as above
// We modify them slightly to return the distance arrays.

void johnson(int n, vector<vector<pair<int, int>>>& adj) {
    // 1. Create a modified graph with a dummy node (index 0)
    vector<vector<pair<int, int>>> modified_adj = adj;
    for (int i = 1; i <= n; i++) {
        modified_adj[0].push_back({i, 0}); // Dummy node 0 connects to all nodes with weight 0
    }

    // 2. Run Bellman-Ford from the dummy node (0) to get h(v)
    vector<int> h(n + 1, INF);
    h[0] = 0;
    // (Run the Bellman-Ford logic here to fill array 'h'. 
    // If it returns false, abort: "Negative cycle detected")

    // 3. Re-weight the original graph to remove negative edges!
    // Formula: w'(u, v) = w(u, v) + h[u] - h[v]
    for (int u = 1; u <= n; u++) {
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int& weight = edge.second; // Reference so we can modify it
            
            weight = weight + h[u] - h[v]; 
        }
    }

    // 4. Run Dijkstra from EVERY node using the new positive weights
    vector<vector<int>> all_pairs_shortest_paths(n + 1, vector<int>(n + 1));

    for (int u = 1; u <= n; u++) {
        // Run Dijkstra from node 'u'
        // Let's assume it returns a vector 'dist' of shortest paths from 'u'
        vector<int> dist_from_u = run_dijkstra(u, n, adj); 

        // 5. Restore the original distances!
        // Formula: D(u, v) = D'(u, v) - h[u] + h[v]
        for (int v = 1; v <= n; v++) {
            if (dist_from_u[v] != INF) {
                all_pairs_shortest_paths[u][v] = dist_from_u[v] - h[u] + h[v];
            } else {
                all_pairs_shortest_paths[u][v] = INF;
            }
        }
    }
    
    // all_pairs_shortest_paths now holds the exact shortest path between any two nodes!
}
