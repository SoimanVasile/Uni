#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int start, int n, vector<vector<int>>& adj) {
    // Initialize distances with -1 (meaning unvisited)
    vector<int> dist(n + 1, -1);
    queue<int> q;

    // Setup source node
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Check all neighbors
        for (int v : adj[u]) {
            if (dist[v] == -1) { // If white/unvisited
                dist[v] = dist[u] + 1; // Update distance
                q.push(v);             // Enqueue
            }
        }
    }
}
