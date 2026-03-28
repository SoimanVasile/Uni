#include "repo_produs.h"
#include "service_produs.h"
#include "ui.h"
#include "validator.h"

int main(){
    RepoProdus repo;
    Validator validator;
    ServiceProdus service(repo, validator);
    UI ui(service);
    ui.run();
}
