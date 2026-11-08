#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>

struct Node {
    Node* next_node;
    int value;
};


auto create_list(int n, int current_number) -> Node*{
    if (current_number == n){
        return nullptr;
        
    }
    
    auto node = new Node;
    node->value = current_number;
    node->next_node = create_list(n, current_number + 1);

    return node;
}

auto recursive_inverse_list(Node* previous_node, Node* cur_node) -> Node*{

    if (cur_node == nullptr){
        return previous_node;
    }

    auto next_node = cur_node -> next_node;
    cur_node -> next_node = previous_node;
    
    return recursive_inverse_list(cur_node, next_node);
}

auto inverse_list(Node* head) -> Node* {

    return recursive_inverse_list(nullptr, head);
}

auto max_value_list(Node* head) -> int {
    if (head->next_node == nullptr){
        return head->value;
    }

    return std::max(head->value, max_value_list(head->next_node));
}

auto print_list(Node* head) -> void{
    if (head == nullptr){
        return;
    }

    std::cout<<head->value<<' ';
    print_list(head->next_node);
}

auto main() -> int{

    std::size_t n = 30;

    auto head = create_list(n, 0);

    head = inverse_list(head);

    std::cout<<"Max value: " << max_value_list(head)<<'\n';
    
    std::cout<< "Lista: ";
    print_list(head);
    return 0;
}
