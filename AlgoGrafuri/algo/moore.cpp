#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; // Representing infinity

void moore(int start, int n, vector<vector<int>>& adj) {
    vector<int> l(n + 1, INF); // Lengths array
    vector<int> p(n + 1, 0);   // Parents array
    queue<int> q;

    l[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int y : adj[x]) {
            if (l[y] == INF) {       // If unvisited
                p[y] = x;            // Record where we came from
                l[y] = l[x] + 1;     // Increment distance
                q.push(y);
            }
        }
    }
}
