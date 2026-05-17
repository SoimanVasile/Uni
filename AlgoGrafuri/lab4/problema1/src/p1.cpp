#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

void solve(char* input_path, char* output_path){
    std::ifstream fin(input_path);

    int n;
    fin>>n;

    vector<int> parent(n);
    vector<int> degree(n, 0);

    for (int i=0; i<n; i++){
        fin>>parent[i];
        if (parent[i] != -1){
            degree[parent[i]]++;
        }
    }

    int ptr=0;
    while (ptr<n && degree[ptr] !=0)
    { ptr++;}
    
    int leaf=ptr;
    vector<int> prufer;
    prufer.reserve(n-1);
    for (int i=0; i<n-1; i++){
        int p=parent[leaf];

        if (p == -1){
            ptr++;
            while (ptr < n && degree[ptr] != 0){
                ptr++;
            }
            leaf = ptr;
            i--;
            continue;
        }

        prufer.push_back(p);

        degree[p]--;
        if (degree[p] == 0 && p < ptr){
            leaf = p;
        } else{
            ptr++;
            while (ptr < n && degree[ptr] != 0){
                ptr++;
            }
            leaf=ptr;
        }
    }

    std::ofstream fout(output_path);
    fout<<prufer.size()<<"\n";
    for (int i=0; i<(int) prufer.size(); i++)
        fout<<prufer[i]<<' ';
    fout<<"\n";
    fout.close();
    fin.close();
}

int main(int argc, char** argv){
    if (argc < 3) return 0;

    solve(argv[1], argv[2]);
}
