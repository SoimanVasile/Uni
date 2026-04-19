#include <fstream>
#include <iostream>
#include <string>

#include "ui.h"
#include "attribute_produs.h"
#include "produs_tip.h"
#include "repo_produs.h"
#include "service_produs.h"
#include "validator.h"

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
    try{
        std::cin>>tip;
    }
    catch(ProdusTipExpection& e){
        std::cerr << e.mesaj();
        return;
    }

    try {
        AttributeProdus attrib(name, producator);
        service_produs.add_produs(attrib, tip, pret);
    } catch (const ValidatorException& e){
        std::cerr << "Validation error: "<< e.get_mesaj() << std::endl;
        return;
    }
    catch (const RepoException& e){
        std::cerr << "Repo Error: " << e.get_mesaj() << std::endl;
        return;
    }
}

void UI::sterge_produs(){
    std::string name, producator;

    std::cout<< "Nume: ";
    std::cin>>name;
    std::cout<< "Producator: ";
    std::cin>>producator;
    
    try{
        service_produs.sterge_produs(name, producator);
    } catch (const ValidatorException& e){
        std::cerr<< "Validation error: " << e.get_mesaj() << std::endl;
        return;
    }
    catch (const RepoException& e){
        std::cerr << "Repo Error: " << e.get_mesaj() << std::endl;
        return;
    }
}

void UI::print(){
    auto lista = service_produs.get_all();
    for (const auto& val : lista){
        std::cout<<val<<' ';
    }
    std::cout<<std::endl;
}

void menu(){
    std::ifstream menuin("menu.txt");
    std::string line;
    while (std::getline(menuin, line)){
        std::cout<<line<<"\n";
    }
}

void UI::modifica_produs(){
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
    try{
        std::cin>>tip;
        return;
    }
    catch(ProdusTipExpection& e){
        std::cerr << e.mesaj();
    }

    try {
        AttributeProdus attrib(name, producator);
        service_produs.modifica_produs(attrib, tip, pret);
    } catch (const ValidatorException& e){
        std::cerr << "Validation error: "<< e.get_mesaj() << std::endl;
        return;
    }
    catch (const RepoException& e){
        std::cerr << "Repo Error: " << e.get_mesaj() << std::endl;
        return;
    }
}

void UI::find_dupa_nume_si_producator(){
    std::string name, producator;

    std::cout<< "Nume: ";
    std::cin>>name;
    std::cout<< "Producator: ";
    std::cin>>producator;

    try {
        service_produs.find_dupa_nume_si_producator(name, producator);
    } catch (const ValidatorException& e){
        std::cerr << "Validation error: "<< e.get_mesaj() << std::endl;
        return;
    }
    catch (const RepoException& e){
        std::cerr << "Repo Error: " << e.get_mesaj() << std::endl;
        return;
    }
}

void UI::filtrare_dupa_pret(){
    float pret;

    std::cout << "Pret: ";
    std::cin >> pret;

    auto lista = service_produs.filtrare_dupa_pret(pret);

    for (const auto& val : lista){
        std::cout<<val<<' ';
    }
    std::cout<<std::endl;
}

void UI::sortare_dupa_pret(){
    auto lista = service_produs.sortare_dupa_pret();

    for (const auto& val : lista){
        std::cout<<val<<' ';
    }
    std::cout<<std::endl;
}

void UI::filtrare_dupa_nume() {
    std::string nume;
    std::cout << "Nume: ";
    std::cin >> nume;

    auto lista = service_produs.filtrare_dupa_nume(nume);
    if (lista.empty()) std::cout << "Nu am gasit produse.\n";
    for (const auto& val : lista) std::cout << val << ' ';
    std::cout << "\n";
}

void UI::filtrare_dupa_producator() {
    std::string producator;
    std::cout << "Producator: ";
    std::cin >> producator;

    auto lista = service_produs.filtrare_dupa_producator(producator);
    if (lista.empty()) std::cout << "Nu am gasit produse.\n";
    for (const auto& val : lista) std::cout << val << ' ';
    std::cout << "\n";
}

void UI::sortare_dupa_nume() {
    auto lista = service_produs.sortare_dupa_nume();
    for (const auto& val : lista) std::cout << val << ' ';
    std::cout << "\n";
}

void UI::sortare_dupa_nume_si_tip() {
    auto lista = service_produs.sortare_dupa_nume_si_tip();
    for (const auto& val : lista) std::cout << val << ' ';
    std::cout << "\n";
}

void UI::run() {
    int exit=0;
    while(!exit){
        int user_input;
        menu();
        std::cout<<"Alege o optiune: ";
        std::cin>>user_input;
        switch (user_input) {
            case 0: {exit=1;break;}
            case 1: {UI::add_produs(); break;}
            case 2: {UI::print(); break;}
            case 3: {UI::sterge_produs(); break;}
            case 4: {UI::modifica_produs(); break;}
            case 5: {UI::find_dupa_nume_si_producator(); break;}
            case 6: {UI::filtrare_dupa_pret(); break;}
            case 7: {UI::sortare_dupa_pret(); break;}
            case 8: {UI::filtrare_dupa_nume(); break;}
            case 9: {UI::filtrare_dupa_producator(); break;}
            case 10: {UI::sortare_dupa_nume(); break;}
            case 11: {UI::sortare_dupa_nume_si_tip(); break;}
            default: {std::cout << "Optiune invalida!\n"; break;}
        }
    }
}
