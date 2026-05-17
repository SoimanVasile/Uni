#pragma once

#include "repo.h"
#include <algorithm>
#include <vector>

class Service {
    private:
        Repo& repo;

    public:
        Service(Repo& r): repo(r) {};
        std::vector<Fusta> get_all(){
            return repo.get_all();
        }

        void inchiriere(int cod){
            auto all = repo.get_all();
            auto it = std::find_if(all.begin(), all.end(), [&](const Fusta& f){
                    return f.get_cod() == cod;
                    });

            if (it != all.end()){
                it->set_disponibilitate();
            }
        }
};
