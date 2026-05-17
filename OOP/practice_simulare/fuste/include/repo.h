#pragma once
#include "domain.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class RepoException {
    private:
        std::string mesaj_eroare;
    public:
        RepoException(const std::string& mesaj) : mesaj_eroare(mesaj){};
                                            
        std::string get_mesaj() const {return mesaj_eroare;}
};

class Repo {
    private:
        std::string file_path;
        std::vector<Fusta> repo;

        void load_from_file(){
            std::ifstream fin(file_path);

            if (!fin.is_open()){
                throw RepoException("Nu sa putut deschide fisieru!\n");
            }

            std::string line;
            while (std::getline(fin, line)){
                if (line.empty()) continue;
                std::stringstream ss(line);
                std::string cod, denumire, marime, pret, disponibilitate;
                std::getline(ss, cod, ';');
                std::getline(ss, denumire, ';');
                std::getline(ss, marime, ';');
                std::getline(ss, pret, ';');
                std::getline(ss, disponibilitate);
                int c = std::stoi(cod);
                float p = std::stof(pret);
                Marime m = string_to_marime(marime);
                bool avab = disponibilitate == "true";
                Fusta fusta(c, denumire, m, p, avab);
                repo.push_back(fusta);
            }
        }

        void save_to_file(){
            std::ofstream fout(file_path);
            
            if (!fout.is_open()){
                throw RepoException("Nu sa putut deschide fisieru!\n");
            }

            for (const Fusta& item : repo){
                fout << item.get_cod() << ";"
                     << item.get_denumire() << ";"
                     << marime_to_string(item.get_marime()) << ";"
                     << item.get_pret() << ";"
                     << (item.get_disponibilitate() ? "true" : "false")
                     << "\n";
            }
        }

    public:
        Repo(std::string file_path) : file_path(file_path){ load_from_file();};
        std::vector<Fusta> get_all(){
            return repo;
        }
};

