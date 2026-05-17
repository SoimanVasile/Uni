#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

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
            return l->get_val() > r->get_val();
        return l->get_freq() > r->get_freq();
    }
};


void generare_cod(BinaryNode* head, std::string cod, std::unordered_map<std::string, char>& code_key){
    if (head == nullptr) return;
    if (head->get_left() == nullptr && head->get_right() == nullptr){
        code_key.insert({cod, head->get_val()});
    }
    generare_cod(head->get_left(), cod+"0", code_key);
    generare_cod(head->get_right(), cod+"1", code_key);
}

void solve(char* input, char* output){
    std::ifstream fin(input);

    int number_letters{};

    fin>>number_letters;

    std::priority_queue<BinaryNode*, std::vector<BinaryNode*>, NodeCmp> pq;
    for (int i=0; i<number_letters+1; i++){
        std::string buffer;
        std::getline(fin, buffer);
        if (buffer.size() <=2) continue;
        char letter = buffer[0];
        std::string number_char = buffer.substr(2);
        int freq=std::stoi(number_char);
        std::cout<<freq<<'\n';
        BinaryNode* node = new BinaryNode(letter, freq);
        pq.push(node);
    }
    
    std::string text;
    std::getline(fin, text);
    fin.close();
    while (pq.size()>1){
        BinaryNode* left = pq.top();
        pq.pop();
        BinaryNode* right = pq.top();
        pq.pop();
        BinaryNode* parent = new BinaryNode('\\', left->get_freq()+right->get_freq());
        parent->set_left(left);
        parent->set_right(right);
        pq.push(parent);
    }

    BinaryNode* head = pq.top();
    std::unordered_map<std::string, char> code_key;
    generare_cod(head, "", code_key);
    std::ofstream fout(output);
    std::string code;
    for (auto val: text){
        code.push_back(val);
        if (code_key.find(code) != code_key.end()){
            fout<<code_key[code];
            code.clear();
        }
    }
    fout.close();
    fin.close();
}
int main(int argc, char** argv){
    if (argc < 3) {std::cout<<"Nu ai introdus fisierul de intrare si iesire!\n"; return 1;}
    solve(argv[1], argv[2]);
    return 0;
}
