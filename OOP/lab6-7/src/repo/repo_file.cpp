#include "repo_file.h"
#include <fstream>
#include <sstream>

RepoFile::RepoFile(const std::string& file_path) : RepoProdus(), file_path(file_path) {
    load_from_file();
}

void RepoFile::load_from_file() {
    std::ifstream fin(file_path);
    if (!fin.is_open()) return;
    
    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string nume, producator, tip_str, pret_str;
        std::getline(ss, nume, ',');
        std::getline(ss, producator, ',');
        std::getline(ss, tip_str, ',');
        std::getline(ss, pret_str, ',');

        std::stringstream ts(tip_str);
        ProdusTip tip;
        ts >> tip;
        float pret = std::stof(pret_str);
        AttributeProdus attr{nume, producator};
        Produs p{attr, tip, pret};
        RepoProdus::add_produs(p);
    }
}

void RepoFile::save_to_file() const {
    std::ofstream fout(file_path);
    if (!fout.is_open()) {
        throw RepoException("Eroare la deschiderea fisierului pentru scriere: " + file_path);
    }
    for (const auto& produs : RepoProdus::get_all()) {
        fout << produs.get_nume() << "," << produs.get_producator() << "," << produs.get_tip() << "," << produs.get_pret() << "\n";
    }
}

void RepoFile::add_produs(const Produs& produs) {
    RepoProdus::add_produs(produs);
    save_to_file();
}

void RepoFile::sterge_produs(const std::string& nume, const std::string& producator) {
    RepoProdus::sterge_produs(nume, producator);
    save_to_file();
}

void RepoFile::modifica_produs(const Produs& produs_nou) {
    RepoProdus::modifica_produs(produs_nou);
    save_to_file();
}
