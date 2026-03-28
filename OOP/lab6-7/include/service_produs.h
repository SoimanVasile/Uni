#ifndef SERVICE_PRODUS_H
#define SERVICE_PRODUS_H

#include <string>
#include "produs_tip.h"
#include "repo_produs.h"
#include "validator.h"
class ServiceProdus{
    private:
        RepoProdus& repo_produs;
        Validator& validator_produs;

    public:

        ServiceProdus(RepoProdus& repo_produs, Validator& validator);

        void add_produs(std::string nume, std::string producator, ProdusTip tip, float pret);

        void print();
};

#endif
