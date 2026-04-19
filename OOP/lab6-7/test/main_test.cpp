#include <iostream>

void test_domain();
void test_produs_tip();
void test_validator();
void test_repo();
void test_service();

int main() {
    test_domain();
    test_produs_tip();
    test_validator();
    test_repo();
    test_service();
    std::cout << "Toate testele au trecut cu succes!\n";
    return 0;
}
