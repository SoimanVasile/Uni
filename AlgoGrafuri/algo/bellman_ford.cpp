#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

// Returns 'true' if successful, or 'false' if a NEGATIVE CYCLE is detected.
bool bellman_ford(int start, int n, vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(n + 1, INF);
    vector<int> parent(n + 1, 0);
    
    dist[start] = 0;

    // Step 1: Relax all edges exactly (V - 1) times
    for (int i = 1; i <= n - 1; i++) {
        for (int u = 1; u <= n; u++) {
            if (dist[u] == INF) continue; // Skip if u is unreachable

            for (auto edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                // RELAXATION
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    // Step 2: Check for negative-weight cycles. 
    // If we can STILL find a shorter path after V-1 loops, a negative cycle exists!
    for (int u = 1; u <= n; u++) {
        if (dist[u] == INF) continue;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                cout << "Error: Graph contains a negative-weight cycle!\n";
                return false; 
            }
        }
    }

    return true; // Success! 'dist' now holds the shortest paths.
}
