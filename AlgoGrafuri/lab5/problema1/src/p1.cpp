#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define INF 1000000007
using std::vector;
using std::queue;
using std::pair;

vector<vector<int>> capacity;

int bfs(int s, int t, vector<int> &parent, int v){
    std::fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while(!q.empty()){
        int elem = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int next=0; next<v; next++){
            if (parent[next] == -1 && capacity[elem][next] > 0){
                parent[next] = elem;
                int new_flow = std::min(flow, capacity[elem][next]);
                if (next == t){
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }
    
    return 0;
}

void solve(char* input, char* output){
    std::ifstream fin(input);
    
    int v, e;
    fin>>v;
    fin>>e;
    capacity.assign(v, vector<int>(v, 0));
    for (int i=0; i<e; i++){
        int x,y,w;
        fin>>x>>y>>w;
        capacity[x][y] += w;
    }
    fin.close();
    
    int s=0,t=v-1;
    int flow=0;
    vector<int> parent(v);
    int new_flow;

    while((new_flow = bfs(s, t, parent, v))){
        flow += new_flow;
        int cur = t;
        while(cur != s){
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    std::ofstream fout(output);
    fout<<flow;
    fout.close();
}

int main(int argc, char** argv){
    if (argc <3){std::cout<<"Nu ati introdus fisierul de intrare si de iesire!\n"; return 1;}

    solve(argv[1], argv[2]);
}
