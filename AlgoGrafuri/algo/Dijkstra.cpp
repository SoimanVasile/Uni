#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; // Representing infinity

// Note: Adjacency list stores pairs of {neighbor_node, edge_weight}
void dijkstra(int start, int n, vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(n + 1, INF);
    vector<int> parent(n + 1, 0);
    
    // Min-Heap setup: stores pairs of {distance, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Setup source node
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int d = pq.top().first;   // Current shortest distance
        int u = pq.top().second;  // Current node
        pq.pop();

        // Optimization: skip if we've already found a strictly better path to u
        if (d > dist[u]) continue;

        // Check all neighbors
        for (auto edge : adj[u]) {
            int v = edge.first;      // Neighbor node
            int weight = edge.second; // Weight of edge (u, v)

            // RELAXATION STEP
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v}); // Push updated distance to the queue
            }
        }
    }
}
