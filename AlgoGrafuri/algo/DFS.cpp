#include <iostream>
#include <vector>

using namespace std;

// Recursive DFS function
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true; // Mark as gray/black
    
    // (Optional) Do something when node is discovered: e.g., record start time

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited); // Go deeper
        }
    }
    
    // (Optional) Do something when node is finished: e.g., record finish time
}

// Wrapper function to start DFS
void start_dfs(int start, int n, vector<vector<int>>& adj) {
    vector<bool> visited(n + 1, false);
    dfs(start, adj, visited);
}
