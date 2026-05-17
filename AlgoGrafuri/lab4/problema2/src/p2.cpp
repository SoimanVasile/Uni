#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

void solve(char* input_path, char* output_path){
    std::ifstream fin(input_path);
    int n;
    fin>>n;

    vector<int> degree(n+1, 0);
    vector<int> parent_vector(n+1, -1);
    vector<int> prufer_coded(n);

    for (int i=0; i<n; i++){
        fin>>prufer_coded[i];
        degree[prufer_coded[i]]++;
    }


    int ptr=0;
    while (ptr < n+1 && degree[ptr]!=0){
        ptr++;
    }

    int leaf=ptr;

    for (auto parent : prufer_coded){
        parent_vector[leaf]=parent;

        degree[parent]--;
        if (degree[parent] == 0 && parent < ptr){
            leaf=parent;
        } else{
            ptr++;
            while (ptr < n+1 && degree[ptr] !=0){
                ptr++;
            }
            leaf=ptr;
        }
    }

    std::ofstream fout(output_path);
    fout<<n+1<<"\n";
    for (auto parent : parent_vector){
        fout<<parent<<' ';
    }
    fout<<"\n";
}

int main(int argc, char** argv){
    if (argc <3) { std::cout<<"Nu ai introdus fisierul de intrare si fisierul de iesire!\n"; return 1;}

    solve(argv[1], argv[2]);
    return 0;
}
