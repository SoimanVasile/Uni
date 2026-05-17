#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using std::vector;
using std::queue;

class Node {
public:
    int height;
    int exceed;
    Node(int h, int e) : height(h), exceed(e) {};
};

const int inf = 100000000;

int n, source, sink; 
vector<vector<int>> capacity;
vector<vector<int>> flow;
vector<Node> nodes;
queue<int> excess_vertices;

void push(int u, int v) {
    int d = std::min(nodes[u].exceed, capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    nodes[u].exceed -= d;
    nodes[v].exceed += d;
    
    if (d && nodes[v].exceed == d && v != source && v != sink) {
        excess_vertices.push(v);
    }
}

void relabel(int u) {
    int d = inf;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = std::min(d, nodes[i].height);
    }
    if (d < inf) {
        nodes[u].height = d + 1;
    }
}

void discharge(int u) {
    while (nodes[u].exceed > 0) {
        bool pushed = false;
        
        for (int v = 0; v < n; v++) {
            if (capacity[u][v] - flow[u][v] > 0 && nodes[u].height == nodes[v].height + 1) {
                push(u, v);
                pushed = true;
                
                if (nodes[u].exceed == 0) {
                    break;
                }
            }
        }
        
        // If we checked all neighbors and couldn't push, we must relabel
        if (!pushed) {
            relabel(u);
        }
    }
}

void solve(char* input, char* output) {
    std::fstream fin(input);
    
    int e;
    fin >> n >> e; 
    
    source = 0;
    sink = n - 1;

    capacity.assign(n, vector<int>(n, 0));
    flow.assign(n, vector<int>(n, 0));
    nodes.assign(n, Node(0, 0));

    for (int i = 0; i < e; i++) {
        int u, v, cap;
        fin >> u >> v >> cap;
        capacity[u][v] = cap; 
    }

    nodes[source].height = n;
    
    for (int v = 0; v < n; v++) {
        if (capacity[source][v] > 0) {
            int d = capacity[source][v];
            flow[source][v] += d;
            flow[v][source] -= d;
            nodes[v].exceed += d;
            nodes[source].exceed -= d;
            
            if (v != sink) {
                excess_vertices.push(v);
            }
        }
    }

    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        
        discharge(u);
    }

    std::ofstream fout(output);
    fout << nodes[sink].exceed;
}

int main(int argc, char** argv) {
    if (argc < 3) { 
        std::cout << "Nu ati introdus fisierul de intrare si de iesire!\n"; 
        return 1;
    }
    solve(argv[1], argv[2]);
    return 0;
}
