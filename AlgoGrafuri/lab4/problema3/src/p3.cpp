#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class BinaryNode {
private:
    char val;
    int freq;
    BinaryNode *left, *right;
public:
    BinaryNode(char val, int freq) : val(val), freq(freq) { left = nullptr; right = nullptr; }
    char get_val() const { return val; }
    int get_freq() const { return freq; }
    BinaryNode* get_left() const { return left; }
    BinaryNode* get_right() const { return right; }
    void set_left(BinaryNode* node) { left = node; }
    void set_right(BinaryNode* node) { right = node; }
};

struct NodeCmp {
    bool operator()(BinaryNode* l, BinaryNode* r) {
        if(l->get_freq() == r->get_freq())
            return l->get_val() > r->get_val(); // tie-breaker pentru a avea un arbore stabil
        return l->get_freq() > r->get_freq();
    }
};

void genereazaCoduri(BinaryNode* root, std::string code, std::unordered_map<char, std::string>& huffmanCode) {
    if (!root) return;

    // Daca nodul este frunza
    if (!root->get_left() && !root->get_right()) {
        huffmanCode[root->get_val()] = code;
    }

    genereazaCoduri(root->get_left(), code + "0", huffmanCode);
    genereazaCoduri(root->get_right(), code + "1", huffmanCode);
}

void solve(char* input, char* output){
    std::unordered_map<char, int> freq;
    std::ifstream fin(input);

    std::string full_text = "";
    std::string buffer;
    while (std::getline(fin, buffer)) {
        full_text += buffer;
        for (auto character : buffer) {
            freq[character]++;
        }
    }
    fin.close();
    
    std::priority_queue<BinaryNode*, std::vector<BinaryNode*>, NodeCmp> pq;

    for (auto val : freq) {
        pq.push(new BinaryNode(val.first, val.second));
    }

    while (pq.size() > 1) {
        BinaryNode* stanga = pq.top(); pq.pop();
        BinaryNode* dreapta = pq.top(); pq.pop();

        BinaryNode* parinte = new BinaryNode('\0', stanga->get_freq() + dreapta->get_freq());
        parinte->set_left(stanga);
        parinte->set_right(dreapta);

        pq.push(parinte);
    }

    BinaryNode* root = pq.top();

    std::unordered_map<char, std::string> huffmanCode;
    genereazaCoduri(root, "", huffmanCode);

    std::ofstream fout(output);
    fout << freq.size() << "\n";
    for (auto item : freq) {
        fout << item.first << ' ' << item.second << "\n";
    }

    std::string textCodat = "";
    for (char c : full_text) {
        textCodat += huffmanCode[c];
    }
    fout << textCodat << "\n";
    
    fout.close();
}

int main(int argc, char** argv){
    if (argc <3) { std::cout<<"Nu ai introdus fisierul de intrare si fisierul de iesire!\n"; return 1;}
    

    solve(argv[1], argv[2]);
    return 0;
}
