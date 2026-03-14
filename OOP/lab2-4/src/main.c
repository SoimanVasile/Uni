#include "test.h"
#include "ui.h"

int main(int argc, char** argv){
    if (argc >= 2){
        if (argv[1][0] == 't')
            run_all();
    }
    else{
    run();
    }
}
