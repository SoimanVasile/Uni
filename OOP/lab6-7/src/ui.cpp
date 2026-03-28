#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "ui.h"
#include "domain_produs.h"
#include "produs_tip.h"
#include "service_produs.h"

UI::UI(ServiceProdus& service) : service_produs(service) {}

void UI::add_produs(){
    std::string name, producator;
    float pret;
    ProdusTip tip;

    std::cout<< "Nume: ";
    std::cin>>name;
    std::cout<< "Producator: ";
    std::cin>>producator;
    std::cout<< "Pret: ";
    std::cin>>pret;
    std::cout<<"Tip: ";
    std::cin>>tip;

    try {
        service_produs.add_produs(name, producator, tip, pret);
    } catch (const std::exception& e){
        std::cerr << "Validation error: "<< e.what() << std::endl;
    }
}

void UI::print(){
    service_produs.print();
}

void menu(){
    std::ifstream menuin("menu.txt");
    std::string line;
    while (std::getline(menuin, line)){
        std::cout<<line<<"\n";
    }
}

void UI::run() {
    int exit=0;
    while(!exit){
        int user_input;
        menu();
        std::cin>>user_input;
        switch (user_input) {
            case 0: {exit=1;break;}
            case 1: {UI::add_produs(); break;}
            case 2: {UI::print(); break;}
        }
    }
}
