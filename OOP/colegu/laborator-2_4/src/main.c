#include "service.h"
#include "ui.h"
#include "test.h"

int main() {
    ruleaza_toate_testele(); 
    
    Repo* r = creeaza_repo();
    Service* s = creeaza_service(r);
    
    run_ui(s);
    
    distruge_service(s);
    distruge_repo(r);
    
    return 0;
}
